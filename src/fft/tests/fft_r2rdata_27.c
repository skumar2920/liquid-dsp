/*
 * Copyright (c) 2011 Joseph Gaeddert
 * Copyright (c) 2011 Virginia Polytechnic Institute & State University
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

//
// autotest fft r2r (real-to-real) data
//

// 27-point real even/odd dft data
float fftdata_r2r_x27[] = {
      1.00000000e+00,   9.67720449e-01,   8.74232948e-01,   7.29134023e-01,
      5.46968460e-01,   3.45309585e-01,   1.42522618e-01,  -4.44371328e-02,
     -2.01871306e-01,  -3.20590228e-01,  -3.96443307e-01,  -4.30132151e-01,
     -4.26421911e-01,  -3.92946303e-01,  -3.38838935e-01,  -2.73413390e-01,
     -2.05070078e-01,  -1.40540510e-01,  -8.45066383e-02,  -3.95672210e-02,
     -6.47628168e-03,   1.54448878e-02,   2.78246514e-02,   3.27720679e-02,
      3.24839540e-02,   2.89606918e-02,   2.38370150e-02 };


// REDFT00
float fftdata_r2r_REDFT00_y27[] = {
      1.90807498e+00,   6.92315578e+00,   1.18128624e+01,   5.63927364e+00,
      6.24250948e-01,   6.22979142e-02,  -2.71553919e-02,   1.96029730e-02,
     -1.47504276e-02,   1.15671754e-02,  -9.38177109e-03,   7.82203674e-03,
     -6.67411089e-03,   5.80593944e-03,  -5.13643026e-03,   4.61196899e-03,
     -4.19497490e-03,   3.86145711e-03,  -3.59269325e-03,   3.37751862e-03,
     -3.20415385e-03,   3.06731090e-03,  -2.96133757e-03,   2.88200378e-03,
     -2.82669067e-03,   2.79450417e-03,  -2.78437138e-03 };


// REDFT10
float fftdata_r2r_REDFT10_y27[] = {
      2.93191195e+00,   7.81435204e+00,   1.25262451e+01,   5.87700558e+00,
      3.13943624e-01,  -2.23003000e-01,  -1.98579907e-01,  -9.58713368e-02,
     -9.68946069e-02,  -5.19125164e-02,  -5.74545190e-02,  -3.24527398e-02,
     -3.75072435e-02,  -2.18437612e-02,  -2.58425809e-02,  -1.53105119e-02,
     -1.83160957e-02,  -1.09222922e-02,  -1.30745629e-02,  -7.76020437e-03,
     -9.17540491e-03,  -5.33153862e-03,  -6.08742610e-03,  -3.34636122e-03,
     -3.48186493e-03,  -1.61480904e-03,  -1.13347173e-03 };


// REDFT01
float fftdata_r2r_REDFT01_y27[] = {
      3.24506021e+00,   1.02413387e+01,   1.02888603e+01,   2.94090056e+00,
      3.01434755e-01,  -3.94552648e-02,   4.12662849e-02,  -3.65541428e-02,
      3.23217735e-02,  -2.86298655e-02,   2.54328623e-02,  -2.26499923e-02,
      2.02035718e-02,  -1.80307329e-02,   1.60805881e-02,  -1.43106822e-02,
      1.26882717e-02,  -1.11882668e-02,   9.78851132e-03,  -8.47033411e-03,
      7.21932389e-03,  -6.02424145e-03,   4.87267971e-03,  -3.75625165e-03,
      2.66467361e-03,  -1.59203156e-03,   5.29353623e-04 };


// REDFT11
float fftdata_r2r_REDFT11_y27[] = {
      4.32605982e+00,   1.13771296e+01,   1.02061100e+01,   2.13518620e+00,
     -1.33218557e-01,  -2.76073009e-01,  -8.56223330e-02,  -1.44742057e-01,
     -2.83730812e-02,  -9.47302654e-02,  -7.39809964e-03,  -6.90608099e-02,
      2.49255938e-03,  -5.37654683e-02,   7.92805944e-03,  -4.37831581e-02,
      1.13052810e-02,  -3.68458964e-02,   1.36666447e-02,  -3.17945704e-02,
      1.55290905e-02,  -2.79758442e-02,   1.71851665e-02,  -2.49931645e-02,
      1.88217703e-02,  -2.25886870e-02,   2.05794629e-02 };


// RODFT00
float fftdata_r2r_RODFT00_y27[] = {
     -3.07457280e+00,   4.34810066e+00,   1.09639254e+01,   7.64511538e+00,
      4.62730789e+00,   3.26789522e+00,   2.68699503e+00,   2.17084169e+00,
      1.91607285e+00,   1.60684299e+00,   1.45886230e+00,   1.24392998e+00,
      1.14396501e+00,   9.81968999e-01,   9.06752288e-01,   7.78145194e-01,
      7.16473997e-01,   6.10574782e-01,   5.56297779e-01,   4.66658950e-01,
      4.16026711e-01,   3.38447809e-01,   2.88945198e-01,   2.20500469e-01,
      1.70261383e-01,   1.08778238e-01,   5.62527180e-02 };


// RODFT10
float fftdata_r2r_RODFT10_y27[] = {
     -3.45587444e+00,   3.69455957e+00,   1.00895662e+01,   7.11557245e+00,
      4.58258820e+00,   3.34214282e+00,   2.84152031e+00,   2.34757495e+00,
      2.14987850e+00,   1.85646343e+00,   1.76226008e+00,   1.56126976e+00,
      1.51575768e+00,   1.36674178e+00,   1.34836006e+00,   1.23211598e+00,
      1.23075652e+00,   1.13685036e+00,   1.14728224e+00,   1.06952679e+00,
      1.08892000e+00,   1.02343559e+00,   1.05029333e+00,   9.94573593e-01,
      1.02823102e+00,   9.80662346e-01,   1.02105260e+00 };


// RODFT01
float fftdata_r2r_RODFT01_y27[] = {
     -2.61891890e+00,  -4.18362617e-02,   9.58289337e+00,   9.41432190e+00,
      5.27894020e+00,   3.62661290e+00,   2.76587272e+00,   2.31010056e+00,
      1.92357457e+00,   1.67965138e+00,   1.44504440e+00,   1.28557563e+00,
      1.12212110e+00,   1.00580621e+00,   8.81629765e-01,   7.90346980e-01,
      6.89975739e-01,   6.14315927e-01,   5.29168069e-01,   4.63644713e-01,
      3.88459831e-01,   3.29564214e-01,   2.60825515e-01,   2.06111193e-01,
      1.41254663e-01,   8.88549462e-02,   2.58288011e-02 };


// RODFT11
float fftdata_r2r_RODFT11_y27[] = {
     -2.72205544e+00,  -1.06129467e+00,   8.21426964e+00,   9.14769840e+00,
      5.52553558e+00,   3.88690162e+00,   3.03581023e+00,   2.59010696e+00,
      2.22776008e+00,   2.00389194e+00,   1.79835343e+00,   1.66311359e+00,
      1.53181064e+00,   1.44247937e+00,   1.35311365e+00,   1.29120958e+00,
      1.22834873e+00,   1.18450797e+00,   1.13985527e+00,   1.10885823e+00,
      1.07762277e+00,   1.05639505e+00,   1.03571594e+00,   1.02242053e+00,
      1.01060724e+00,   1.00419796e+00,   1.00035369e+00 };


