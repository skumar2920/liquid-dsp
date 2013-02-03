/*
 * Copyright (c) 2013 Joseph Gaeddert
 *
 * This file is part of liquid.
 *
 * liquid is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * liquid is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with liquid.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "autotest/autotest.h"
#include "liquid.h"

// 
// AUTOTEST : test multi-stage arbitrary resampler
//
void autotest_msresamp_crcf()
{
    // options
    unsigned int m = 13;        // filter semi-length (filter delay)
    float r=0.127115323f;       // resampling rate (output/input)
    float As=60.0f;             // resampling filter stop-band attenuation [dB]
    unsigned int n=1200;        // number of input samples
    float fx=0.0254230646f;     // complex input sinusoid frequency (0.2*r)
    //float bw=0.45f;             // resampling filter bandwidth
    //unsigned int npfb=64;       // number of filters in bank (timing resolution)

    unsigned int i;

    // number of input samples (zero-padded)
    unsigned int nx = n + m;

    // output buffer with extra padding for good measure
    unsigned int y_len = (unsigned int) ceilf(1.1 * nx * r) + 4;

    // arrays
    float complex x[nx];
    float complex y[y_len];

    // create resampler
    msresamp_crcf q = msresamp_crcf_create(r,As);

    // generate input signal
    float wsum = 0.0f;
    for (i=0; i<nx; i++) {
        // compute window
        float w = i < n ? kaiser(i, n, 10.0f, 0.0f) : 0.0f;

        // apply window to complex sinusoid
        x[i] = cexpf(_Complex_I*2*M_PI*fx*i) * w;

        // accumulate window
        wsum += w;
    }

    // resample
    unsigned int ny=0;
    unsigned int nw;
    for (i=0; i<nx; i++) {
        // execute resampler, storing in output buffer
        msresamp_crcf_execute(q, &x[i], 1, &y[ny], &nw);

        // increment output size
        ny += nw;
    }

    // clean up allocated objects
    msresamp_crcf_destroy(q);

    // check that the actual resampling rate is close to the target
    float r_actual = (float)ny / (float)nx;
    if (liquid_autotest_verbose) {
        printf("  desired resampling rate   :   %12.8f\n", r);
        printf("  measured resampling rate  :   %12.8f (%u/%u)\n", r_actual, ny, nx);
    }
    CONTEND_DELTA( r_actual, r, 0.01f );

    // run FFT and ensure that carrier has moved and that image
    // frequencies and distortion have been adequately suppressed
    unsigned int nfft = 1 << liquid_nextpow2(ny);
    float complex yfft[nfft];   // fft input
    float complex Yfft[nfft];   // fft output
    for (i=0; i<nfft; i++)
        yfft[i] = i < ny ? y[i] : 0.0f;
    fft_run(nfft, yfft, Yfft, FFT_FORWARD, 0);
    fft_shift(Yfft, nfft);  // run FFT shift

    // find peak frequency
    float Ypeak = 0.0f;
    float fpeak = 0.0f;
    for (i=0; i<nfft; i++) {
        // normalized output frequency
        float f = (float)i/(float)nfft - 0.5f;

        // scale FFT output appropriately
        Yfft[i] *= 1.0f / (r * wsum);

        float Ymag = cabsf(Yfft[i]);
        if (Ymag > Ypeak || i==0) {
            Ypeak = Ymag;
            fpeak = f;
        }
    }

    // print results and check frequency location
    float fy = fx / r;      // expected output frequency
    if (liquid_autotest_verbose) {
        printf("  peak spectrum             :   %12.8f (expected 1.0)\n", Ypeak);
        printf("  peak frequency            :   %12.8f (expected %-12.8f)\n", fpeak, fy);
    }
    CONTEND_DELTA( Ypeak, 1.0f, 0.05f );  // peak should be 1
    CONTEND_DELTA( fpeak, fy,   0.01f );  // value should be nearly 0.2

    // check magnitude
    float max_sidelobe = -1e9f;     // maximum side-lobe [dB]
    float main_lobe_width = 0.07f;  // TODO: figure this out from Kaiser's equations
    for (i=0; i<nfft; i++) {
        // normalized output frequency
        float f = (float)i/(float)nfft - 0.5f;

        // ignore frequencies within a certain range of
        // signal frequency
        if ( fabsf(f-fy) < main_lobe_width ) {
            // skip
        } else {
            // check output spectral content is sufficiently suppressed
            float YdB = 20*log10f(cabsf(Yfft[i]));
            max_sidelobe = YdB > max_sidelobe ? YdB : max_sidelobe;
        }
    }
    if (liquid_autotest_verbose)
        printf("  max sidelobe              :   %12.8f dB (expected at least %.2f dB)\n", max_sidelobe, -As);
    CONTEND_LESS_THAN( max_sidelobe, -As );

#if 0
    // export results for debugging
    char filename[] = "msresamp_crcf_autotest.m";
    FILE*fid = fopen(filename,"w");
    fprintf(fid,"%% %s: auto-generated file\n",filename);
    fprintf(fid,"clear all;\n");
    fprintf(fid,"close all;\n");
    fprintf(fid,"r    = %12.8f;\n", r);
    fprintf(fid,"nx   = %u;\n", nx);
    fprintf(fid,"ny   = %u;\n", ny);
    fprintf(fid,"nfft = %u;\n", nfft);

    fprintf(fid,"Y = zeros(1,nfft);\n");
    for (i=0; i<nfft; i++)
        fprintf(fid,"Y(%3u) = %12.4e + j*%12.4e;\n", i+1, crealf(Yfft[i]), cimagf(Yfft[i]));

    fprintf(fid,"\n\n");
    fprintf(fid,"%% plot frequency-domain result\n");
    fprintf(fid,"f=[0:(nfft-1)]/nfft-0.5;\n");
    fprintf(fid,"figure;\n");
    fprintf(fid,"plot(f,20*log10(abs(Y)),'Color',[0.25 0.5 0.0],'LineWidth',2);\n");
    fprintf(fid,"grid on;\n");
    fprintf(fid,"xlabel('normalized frequency');\n");
    fprintf(fid,"ylabel('PSD [dB]');\n");
    fprintf(fid,"axis([-0.5 0.5 -120 20]);\n");

    fclose(fid);
    printf("results written to %s\n",filename);
#endif
}
