/* ============================================================
 * Authors     : Pawel T. 
 *                Gilles Caulier 
 * Date        : 2005-03-11
 * Description : White Balance Black Body array calibrate 
 *               in Kelvin.
 * 
 * Copyright 2004-2005 by Pawel T. Jochym <Jochym jochym at ifj edu pl>
 * Copyright 2005-2007 by Gilles Caulier <caulier dot gilles at gmail dot com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * ============================================================ */

#ifndef BLACKBODY_H
#define BLACKBODY_H

namespace Digikam
{

static const float blackBodyWhiteBalance[][3] = 
{
    /*    2000 */ { 1.0000, 0.5977, 0.0120 }, 
    /*    2010 */ { 1.0000, 0.6021, 0.0140 }, 
    /*    2020 */ { 1.0000, 0.6064, 0.0160 }, 
    /*    2030 */ { 1.0000, 0.6107, 0.0181 }, 
    /*    2040 */ { 1.0000, 0.6150, 0.0202 }, 
    /*    2050 */ { 1.0000, 0.6193, 0.0223 }, 
    /*    2060 */ { 1.0000, 0.6236, 0.0244 }, 
    /*    2070 */ { 1.0000, 0.6278, 0.0265 }, 
    /*    2080 */ { 1.0000, 0.6320, 0.0287 }, 
    /*    2090 */ { 1.0000, 0.6362, 0.0309 }, 
    /*    2100 */ { 1.0000, 0.6403, 0.0331 }, 
    /*    2110 */ { 1.0000, 0.6444, 0.0353 }, 
    /*    2120 */ { 1.0000, 0.6485, 0.0375 }, 
    /*    2130 */ { 1.0000, 0.6526, 0.0398 }, 
    /*    2140 */ { 1.0000, 0.6566, 0.0421 }, 
    /*    2150 */ { 1.0000, 0.6606, 0.0444 }, 
    /*    2160 */ { 1.0000, 0.6646, 0.0467 }, 
    /*    2170 */ { 1.0000, 0.6686, 0.0491 }, 
    /*    2180 */ { 1.0000, 0.6725, 0.0514 }, 
    /*    2190 */ { 1.0000, 0.6764, 0.0538 }, 
    /*    2200 */ { 1.0000, 0.6803, 0.0562 }, 
    /*    2210 */ { 1.0000, 0.6842, 0.0586 }, 
    /*    2220 */ { 1.0000, 0.6880, 0.0611 }, 
    /*    2230 */ { 1.0000, 0.6918, 0.0635 }, 
    /*    2240 */ { 1.0000, 0.6956, 0.0660 }, 
    /*    2250 */ { 1.0000, 0.6994, 0.0685 }, 
    /*    2260 */ { 1.0000, 0.7031, 0.0710 }, 
    /*    2270 */ { 1.0000, 0.7068, 0.0735 }, 
    /*    2280 */ { 1.0000, 0.7105, 0.0761 }, 
    /*    2290 */ { 1.0000, 0.7142, 0.0786 }, 
    /*    2300 */ { 1.0000, 0.7178, 0.0812 }, 
    /*    2310 */ { 1.0000, 0.7214, 0.0838 }, 
    /*    2320 */ { 1.0000, 0.7250, 0.0864 }, 
    /*    2330 */ { 1.0000, 0.7286, 0.0890 }, 
    /*    2340 */ { 1.0000, 0.7321, 0.0917 }, 
    /*    2350 */ { 1.0000, 0.7356, 0.0943 }, 
    /*    2360 */ { 1.0000, 0.7391, 0.0970 }, 
    /*    2370 */ { 1.0000, 0.7426, 0.0997 }, 
    /*    2380 */ { 1.0000, 0.7461, 0.1024 }, 
    /*    2390 */ { 1.0000, 0.7495, 0.1051 }, 
    /*    2400 */ { 1.0000, 0.7529, 0.1079 }, 
    /*    2410 */ { 1.0000, 0.7563, 0.1106 }, 
    /*    2420 */ { 1.0000, 0.7596, 0.1134 }, 
    /*    2430 */ { 1.0000, 0.7630, 0.1162 }, 
    /*    2440 */ { 1.0000, 0.7663, 0.1189 }, 
    /*    2450 */ { 1.0000, 0.7696, 0.1217 }, 
    /*    2460 */ { 1.0000, 0.7728, 0.1246 }, 
    /*    2470 */ { 1.0000, 0.7761, 0.1274 }, 
    /*    2480 */ { 1.0000, 0.7793, 0.1302 }, 
    /*    2490 */ { 1.0000, 0.7825, 0.1331 }, 
    /*    2500 */ { 1.0000, 0.7857, 0.1360 }, 
    /*    2510 */ { 1.0000, 0.7889, 0.1388 }, 
    /*    2520 */ { 1.0000, 0.7920, 0.1417 }, 
    /*    2530 */ { 1.0000, 0.7951, 0.1446 }, 
    /*    2540 */ { 1.0000, 0.7982, 0.1476 }, 
    /*    2550 */ { 1.0000, 0.8013, 0.1505 }, 
    /*    2560 */ { 1.0000, 0.8043, 0.1534 }, 
    /*    2570 */ { 1.0000, 0.8074, 0.1564 }, 
    /*    2580 */ { 1.0000, 0.8104, 0.1593 }, 
    /*    2590 */ { 1.0000, 0.8134, 0.1623 }, 
    /*    2600 */ { 1.0000, 0.8163, 0.1653 }, 
    /*    2610 */ { 1.0000, 0.8193, 0.1683 }, 
    /*    2620 */ { 1.0000, 0.8222, 0.1713 }, 
    /*    2630 */ { 1.0000, 0.8251, 0.1743 }, 
    /*    2640 */ { 1.0000, 0.8280, 0.1773 }, 
    /*    2650 */ { 1.0000, 0.8309, 0.1804 }, 
    /*    2660 */ { 1.0000, 0.8337, 0.1834 }, 
    /*    2670 */ { 1.0000, 0.8365, 0.1865 }, 
    /*    2680 */ { 1.0000, 0.8393, 0.1895 }, 
    /*    2690 */ { 1.0000, 0.8421, 0.1926 }, 
    /*    2700 */ { 1.0000, 0.8449, 0.1957 }, 
    /*    2710 */ { 1.0000, 0.8476, 0.1988 }, 
    /*    2720 */ { 1.0000, 0.8504, 0.2019 }, 
    /*    2730 */ { 1.0000, 0.8531, 0.2050 }, 
    /*    2740 */ { 1.0000, 0.8558, 0.2081 }, 
    /*    2750 */ { 1.0000, 0.8585, 0.2112 }, 
    /*    2760 */ { 1.0000, 0.8611, 0.2144 }, 
    /*    2770 */ { 1.0000, 0.8637, 0.2175 }, 
    /*    2780 */ { 1.0000, 0.8664, 0.2206 }, 
    /*    2790 */ { 1.0000, 0.8690, 0.2238 }, 
    /*    2800 */ { 1.0000, 0.8715, 0.2269 }, 
    /*    2810 */ { 1.0000, 0.8741, 0.2301 }, 
    /*    2820 */ { 1.0000, 0.8766, 0.2333 }, 
    /*    2830 */ { 1.0000, 0.8792, 0.2365 }, 
    /*    2840 */ { 1.0000, 0.8817, 0.2397 }, 
    /*    2850 */ { 1.0000, 0.8842, 0.2429 }, 
    /*    2860 */ { 1.0000, 0.8866, 0.2461 }, 
    /*    2870 */ { 1.0000, 0.8891, 0.2493 }, 
    /*    2880 */ { 1.0000, 0.8915, 0.2525 }, 
    /*    2890 */ { 1.0000, 0.8940, 0.2557 }, 
    /*    2900 */ { 1.0000, 0.8964, 0.2589 }, 
    /*    2910 */ { 1.0000, 0.8987, 0.2621 }, 
    /*    2920 */ { 1.0000, 0.9011, 0.2654 }, 
    /*    2930 */ { 1.0000, 0.9035, 0.2686 }, 
    /*    2940 */ { 1.0000, 0.9058, 0.2719 }, 
    /*    2950 */ { 1.0000, 0.9081, 0.2751 }, 
    /*    2960 */ { 1.0000, 0.9104, 0.2784 }, 
    /*    2970 */ { 1.0000, 0.9127, 0.2816 }, 
    /*    2980 */ { 1.0000, 0.9150, 0.2849 }, 
    /*    2990 */ { 1.0000, 0.9172, 0.2882 }, 
    /*    3000 */ { 1.0000, 0.9195, 0.2914 }, 
    /*    3010 */ { 1.0000, 0.9217, 0.2947 }, 
    /*    3020 */ { 1.0000, 0.9239, 0.2980 }, 
    /*    3030 */ { 1.0000, 0.9261, 0.3013 }, 
    /*    3040 */ { 1.0000, 0.9283, 0.3046 }, 
    /*    3050 */ { 1.0000, 0.9304, 0.3079 }, 
    /*    3060 */ { 1.0000, 0.9326, 0.3112 }, 
    /*    3070 */ { 1.0000, 0.9347, 0.3145 }, 
    /*    3080 */ { 1.0000, 0.9368, 0.3178 }, 
    /*    3090 */ { 1.0000, 0.9389, 0.3211 }, 
    /*    3100 */ { 1.0000, 0.9410, 0.3244 }, 
    /*    3110 */ { 1.0000, 0.9430, 0.3277 }, 
    /*    3120 */ { 1.0000, 0.9451, 0.3310 }, 
    /*    3130 */ { 1.0000, 0.9471, 0.3343 }, 
    /*    3140 */ { 1.0000, 0.9492, 0.3376 }, 
    /*    3150 */ { 1.0000, 0.9512, 0.3410 }, 
    /*    3160 */ { 1.0000, 0.9532, 0.3443 }, 
    /*    3170 */ { 1.0000, 0.9551, 0.3476 }, 
    /*    3180 */ { 1.0000, 0.9571, 0.3509 }, 
    /*    3190 */ { 1.0000, 0.9590, 0.3543 }, 
    /*    3200 */ { 1.0000, 0.9610, 0.3576 }, 
    /*    3210 */ { 1.0000, 0.9629, 0.3609 }, 
    /*    3220 */ { 1.0000, 0.9648, 0.3643 }, 
    /*    3230 */ { 1.0000, 0.9667, 0.3676 }, 
    /*    3240 */ { 1.0000, 0.9686, 0.3709 }, 
    /*    3250 */ { 1.0000, 0.9705, 0.3743 }, 
    /*    3260 */ { 1.0000, 0.9723, 0.3776 }, 
    /*    3270 */ { 1.0000, 0.9741, 0.3810 }, 
    /*    3280 */ { 1.0000, 0.9760, 0.3843 }, 
    /*    3290 */ { 1.0000, 0.9778, 0.3876 }, 
    /*    3300 */ { 1.0000, 0.9796, 0.3910 }, 
    /*    3310 */ { 1.0000, 0.9814, 0.3943 }, 
    /*    3320 */ { 1.0000, 0.9831, 0.3977 }, 
    /*    3330 */ { 1.0000, 0.9849, 0.4010 }, 
    /*    3340 */ { 1.0000, 0.9867, 0.4044 }, 
    /*    3350 */ { 1.0000, 0.9884, 0.4077 }, 
    /*    3360 */ { 1.0000, 0.9901, 0.4111 }, 
    /*    3370 */ { 1.0000, 0.9918, 0.4144 }, 
    /*    3380 */ { 1.0000, 0.9935, 0.4177 }, 
    /*    3390 */ { 1.0000, 0.9952, 0.4211 }, 
    /*    3400 */ { 1.0000, 0.9969, 0.4244 }, 
    /*    3410 */ { 1.0000, 0.9985, 0.4278 }, 
    /*    3420 */ { 1.0000, 1.0000, 0.4311 }, 
    /*    3430 */ { 1.0000, 1.0000, 0.4345 }, 
    /*    3440 */ { 1.0000, 1.0000, 0.4378 }, 
    /*    3450 */ { 1.0000, 1.0000, 0.4412 }, 
    /*    3460 */ { 1.0000, 1.0000, 0.4445 }, 
    /*    3470 */ { 1.0000, 1.0000, 0.4479 }, 
    /*    3480 */ { 0.9992, 1.0000, 0.4512 }, 
    /*    3490 */ { 0.9977, 1.0000, 0.4545 }, 
    /*    3500 */ { 0.9962, 1.0000, 0.4579 }, 
    /*    3510 */ { 0.9947, 1.0000, 0.4612 }, 
    /*    3520 */ { 0.9932, 1.0000, 0.4646 }, 
    /*    3530 */ { 0.9918, 1.0000, 0.4679 }, 
    /*    3540 */ { 0.9903, 1.0000, 0.4712 }, 
    /*    3550 */ { 0.9888, 1.0000, 0.4746 }, 
    /*    3560 */ { 0.9874, 1.0000, 0.4779 }, 
    /*    3570 */ { 0.9859, 1.0000, 0.4812 }, 
    /*    3580 */ { 0.9845, 1.0000, 0.4846 }, 
    /*    3590 */ { 0.9830, 1.0000, 0.4879 }, 
    /*    3600 */ { 0.9816, 1.0000, 0.4912 }, 
    /*    3610 */ { 0.9802, 1.0000, 0.4945 }, 
    /*    3620 */ { 0.9788, 1.0000, 0.4979 }, 
    /*    3630 */ { 0.9773, 1.0000, 0.5012 }, 
    /*    3640 */ { 0.9759, 1.0000, 0.5045 }, 
    /*    3650 */ { 0.9745, 1.0000, 0.5078 }, 
    /*    3660 */ { 0.9731, 1.0000, 0.5111 }, 
    /*    3670 */ { 0.9717, 1.0000, 0.5144 }, 
    /*    3680 */ { 0.9703, 1.0000, 0.5178 }, 
    /*    3690 */ { 0.9689, 1.0000, 0.5211 }, 
    /*    3700 */ { 0.9676, 1.0000, 0.5244 }, 
    /*    3710 */ { 0.9662, 1.0000, 0.5277 }, 
    /*    3720 */ { 0.9648, 1.0000, 0.5310 }, 
    /*    3730 */ { 0.9634, 1.0000, 0.5343 }, 
    /*    3740 */ { 0.9621, 1.0000, 0.5376 }, 
    /*    3750 */ { 0.9607, 1.0000, 0.5409 }, 
    /*    3760 */ { 0.9594, 1.0000, 0.5442 }, 
    /*    3770 */ { 0.9580, 1.0000, 0.5474 }, 
    /*    3780 */ { 0.9567, 1.0000, 0.5507 }, 
    /*    3790 */ { 0.9553, 1.0000, 0.5540 }, 
    /*    3800 */ { 0.9540, 1.0000, 0.5573 }, 
    /*    3810 */ { 0.9527, 1.0000, 0.5606 }, 
    /*    3820 */ { 0.9514, 1.0000, 0.5638 }, 
    /*    3830 */ { 0.9500, 1.0000, 0.5671 }, 
    /*    3840 */ { 0.9487, 1.0000, 0.5704 }, 
    /*    3850 */ { 0.9474, 1.0000, 0.5736 }, 
    /*    3860 */ { 0.9461, 1.0000, 0.5769 }, 
    /*    3870 */ { 0.9448, 1.0000, 0.5802 }, 
    /*    3880 */ { 0.9435, 1.0000, 0.5834 }, 
    /*    3890 */ { 0.9422, 1.0000, 0.5867 }, 
    /*    3900 */ { 0.9409, 1.0000, 0.5899 }, 
    /*    3910 */ { 0.9397, 1.0000, 0.5932 }, 
    /*    3920 */ { 0.9384, 1.0000, 0.5964 }, 
    /*    3930 */ { 0.9371, 1.0000, 0.5996 }, 
    /*    3940 */ { 0.9358, 1.0000, 0.6029 }, 
    /*    3950 */ { 0.9346, 1.0000, 0.6061 }, 
    /*    3960 */ { 0.9333, 1.0000, 0.6093 }, 
    /*    3970 */ { 0.9321, 1.0000, 0.6126 }, 
    /*    3980 */ { 0.9308, 1.0000, 0.6158 }, 
    /*    3990 */ { 0.9296, 1.0000, 0.6190 }, 
    /*    4000 */ { 0.9283, 1.0000, 0.6222 }, 
    /*    4010 */ { 0.9271, 1.0000, 0.6254 }, 
    /*    4020 */ { 0.9259, 1.0000, 0.6286 }, 
    /*    4030 */ { 0.9247, 1.0000, 0.6318 }, 
    /*    4040 */ { 0.9234, 1.0000, 0.6350 }, 
    /*    4050 */ { 0.9222, 1.0000, 0.6382 }, 
    /*    4060 */ { 0.9210, 1.0000, 0.6414 }, 
    /*    4070 */ { 0.9198, 1.0000, 0.6446 }, 
    /*    4080 */ { 0.9186, 1.0000, 0.6478 }, 
    /*    4090 */ { 0.9174, 1.0000, 0.6509 }, 
    /*    4100 */ { 0.9162, 1.0000, 0.6541 }, 
    /*    4110 */ { 0.9150, 1.0000, 0.6573 }, 
    /*    4120 */ { 0.9138, 1.0000, 0.6605 }, 
    /*    4130 */ { 0.9126, 1.0000, 0.6636 }, 
    /*    4140 */ { 0.9115, 1.0000, 0.6668 }, 
    /*    4150 */ { 0.9103, 1.0000, 0.6699 }, 
    /*    4160 */ { 0.9091, 1.0000, 0.6731 }, 
    /*    4170 */ { 0.9080, 1.0000, 0.6762 }, 
    /*    4180 */ { 0.9068, 1.0000, 0.6794 }, 
    /*    4190 */ { 0.9056, 1.0000, 0.6825 }, 
    /*    4200 */ { 0.9045, 1.0000, 0.6856 }, 
    /*    4210 */ { 0.9033, 1.0000, 0.6887 }, 
    /*    4220 */ { 0.9022, 1.0000, 0.6919 }, 
    /*    4230 */ { 0.9011, 1.0000, 0.6950 }, 
    /*    4240 */ { 0.8999, 1.0000, 0.6981 }, 
    /*    4250 */ { 0.8988, 1.0000, 0.7012 }, 
    /*    4260 */ { 0.8974, 1.0000, 0.7041 }, 
    /*    4270 */ { 0.8960, 1.0000, 0.7070 }, 
    /*    4280 */ { 0.8946, 1.0000, 0.7098 }, 
    /*    4290 */ { 0.8932, 1.0000, 0.7127 }, 
    /*    4300 */ { 0.8918, 1.0000, 0.7155 }, 
    /*    4310 */ { 0.8904, 1.0000, 0.7184 }, 
    /*    4320 */ { 0.8890, 1.0000, 0.7212 }, 
    /*    4330 */ { 0.8876, 1.0000, 0.7240 }, 
    /*    4340 */ { 0.8862, 1.0000, 0.7269 }, 
    /*    4350 */ { 0.8849, 1.0000, 0.7297 }, 
    /*    4360 */ { 0.8835, 1.0000, 0.7325 }, 
    /*    4370 */ { 0.8821, 1.0000, 0.7353 }, 
    /*    4380 */ { 0.8808, 1.0000, 0.7381 }, 
    /*    4390 */ { 0.8795, 1.0000, 0.7409 }, 
    /*    4400 */ { 0.8781, 1.0000, 0.7437 }, 
    /*    4410 */ { 0.8768, 1.0000, 0.7465 }, 
    /*    4420 */ { 0.8755, 1.0000, 0.7493 }, 
    /*    4430 */ { 0.8742, 1.0000, 0.7521 }, 
    /*    4440 */ { 0.8729, 1.0000, 0.7549 }, 
    /*    4450 */ { 0.8716, 1.0000, 0.7576 }, 
    /*    4460 */ { 0.8703, 1.0000, 0.7604 }, 
    /*    4470 */ { 0.8690, 1.0000, 0.7632 }, 
    /*    4480 */ { 0.8677, 1.0000, 0.7659 }, 
    /*    4490 */ { 0.8664, 1.0000, 0.7687 }, 
    /*    4500 */ { 0.8652, 1.0000, 0.7714 }, 
    /*    4510 */ { 0.8639, 1.0000, 0.7742 }, 
    /*    4520 */ { 0.8627, 1.0000, 0.7769 }, 
    /*    4530 */ { 0.8614, 1.0000, 0.7797 }, 
    /*    4540 */ { 0.8602, 1.0000, 0.7824 }, 
    /*    4550 */ { 0.8589, 1.0000, 0.7851 }, 
    /*    4560 */ { 0.8577, 1.0000, 0.7879 }, 
    /*    4570 */ { 0.8565, 1.0000, 0.7906 }, 
    /*    4580 */ { 0.8553, 1.0000, 0.7933 }, 
    /*    4590 */ { 0.8541, 1.0000, 0.7960 }, 
    /*    4600 */ { 0.8529, 1.0000, 0.7987 }, 
    /*    4610 */ { 0.8517, 1.0000, 0.8014 }, 
    /*    4620 */ { 0.8505, 1.0000, 0.8041 }, 
    /*    4630 */ { 0.8493, 1.0000, 0.8068 }, 
    /*    4640 */ { 0.8481, 1.0000, 0.8095 }, 
    /*    4650 */ { 0.8469, 1.0000, 0.8122 }, 
    /*    4660 */ { 0.8458, 1.0000, 0.8148 }, 
    /*    4670 */ { 0.8446, 1.0000, 0.8175 }, 
    /*    4680 */ { 0.8434, 1.0000, 0.8202 }, 
    /*    4690 */ { 0.8423, 1.0000, 0.8228 }, 
    /*    4700 */ { 0.8411, 1.0000, 0.8255 }, 
    /*    4710 */ { 0.8400, 1.0000, 0.8282 }, 
    /*    4720 */ { 0.8389, 1.0000, 0.8308 }, 
    /*    4730 */ { 0.8377, 1.0000, 0.8335 }, 
    /*    4740 */ { 0.8366, 1.0000, 0.8361 }, 
    /*    4750 */ { 0.8355, 1.0000, 0.8387 }, 
    /*    4760 */ { 0.8344, 1.0000, 0.8414 }, 
    /*    4770 */ { 0.8333, 1.0000, 0.8440 }, 
    /*    4780 */ { 0.8322, 1.0000, 0.8466 }, 
    /*    4790 */ { 0.8311, 1.0000, 0.8492 }, 
    /*    4800 */ { 0.8300, 1.0000, 0.8518 }, 
    /*    4810 */ { 0.8289, 1.0000, 0.8544 }, 
    /*    4820 */ { 0.8278, 1.0000, 0.8570 }, 
    /*    4830 */ { 0.8268, 1.0000, 0.8596 }, 
    /*    4840 */ { 0.8257, 1.0000, 0.8622 }, 
    /*    4850 */ { 0.8246, 1.0000, 0.8648 }, 
    /*    4860 */ { 0.8236, 1.0000, 0.8674 }, 
    /*    4870 */ { 0.8225, 1.0000, 0.8700 }, 
    /*    4880 */ { 0.8215, 1.0000, 0.8725 }, 
    /*    4890 */ { 0.8204, 1.0000, 0.8751 }, 
    /*    4900 */ { 0.8194, 1.0000, 0.8777 }, 
    /*    4910 */ { 0.8183, 1.0000, 0.8802 }, 
    /*    4920 */ { 0.8173, 1.0000, 0.8828 }, 
    /*    4930 */ { 0.8163, 1.0000, 0.8853 }, 
    /*    4940 */ { 0.8153, 1.0000, 0.8879 }, 
    /*    4950 */ { 0.8143, 1.0000, 0.8904 }, 
    /*    4960 */ { 0.8132, 1.0000, 0.8930 }, 
    /*    4970 */ { 0.8122, 1.0000, 0.8955 }, 
    /*    4980 */ { 0.8112, 1.0000, 0.8980 }, 
    /*    4990 */ { 0.8102, 1.0000, 0.9005 }, 
    /*    5000 */ { 0.8093, 1.0000, 0.9031 }, 
    /*    5010 */ { 0.8083, 1.0000, 0.9056 }, 
    /*    5020 */ { 0.8073, 1.0000, 0.9081 }, 
    /*    5030 */ { 0.8063, 1.0000, 0.9106 }, 
    /*    5040 */ { 0.8053, 1.0000, 0.9131 }, 
    /*    5050 */ { 0.8044, 1.0000, 0.9156 }, 
    /*    5060 */ { 0.8034, 1.0000, 0.9181 }, 
    /*    5070 */ { 0.8024, 1.0000, 0.9206 }, 
    /*    5080 */ { 0.8015, 1.0000, 0.9230 }, 
    /*    5090 */ { 0.8005, 1.0000, 0.9255 }, 
    /*    5100 */ { 0.7996, 1.0000, 0.9280 }, 
    /*    5110 */ { 0.7986, 1.0000, 0.9305 }, 
    /*    5120 */ { 0.7977, 1.0000, 0.9329 }, 
    /*    5130 */ { 0.7968, 1.0000, 0.9354 }, 
    /*    5140 */ { 0.7958, 1.0000, 0.9378 }, 
    /*    5150 */ { 0.7949, 1.0000, 0.9403 }, 
    /*    5160 */ { 0.7940, 1.0000, 0.9427 }, 
    /*    5170 */ { 0.7931, 1.0000, 0.9452 }, 
    /*    5180 */ { 0.7922, 1.0000, 0.9476 }, 
    /*    5190 */ { 0.7913, 1.0000, 0.9500 }, 
    /*    5200 */ { 0.7904, 1.0000, 0.9524 }, 
    /*    5210 */ { 0.7895, 1.0000, 0.9549 }, 
    /*    5220 */ { 0.7886, 1.0000, 0.9573 }, 
    /*    5230 */ { 0.7877, 1.0000, 0.9597 }, 
    /*    5240 */ { 0.7868, 1.0000, 0.9621 }, 
    /*    5250 */ { 0.7859, 1.0000, 0.9645 }, 
    /*    5260 */ { 0.7850, 1.0000, 0.9669 }, 
    /*    5270 */ { 0.7841, 1.0000, 0.9693 }, 
    /*    5280 */ { 0.7833, 1.0000, 0.9717 }, 
    /*    5290 */ { 0.7824, 1.0000, 0.9741 }, 
    /*    5300 */ { 0.7815, 1.0000, 0.9764 }, 
    /*    5310 */ { 0.7807, 1.0000, 0.9788 }, 
    /*    5320 */ { 0.7798, 1.0000, 0.9812 }, 
    /*    5330 */ { 0.7790, 1.0000, 0.9835 }, 
    /*    5340 */ { 0.7781, 1.0000, 0.9859 }, 
    /*    5350 */ { 0.7773, 1.0000, 0.9883 }, 
    /*    5360 */ { 0.7764, 1.0000, 0.9906 }, 
    /*    5370 */ { 0.7756, 1.0000, 0.9930 }, 
    /*    5380 */ { 0.7748, 1.0000, 0.9953 }, 
    /*    5390 */ { 0.7739, 1.0000, 0.9976 }, 
    /*    5400 */ { 0.7731, 1.0000, 1.0000 }, 
    /*    5410 */ { 0.7723, 1.0000, 1.0000 }, 
    /*    5420 */ { 0.7715, 1.0000, 1.0000 }, 
    /*    5430 */ { 0.7706, 1.0000, 1.0000 }, 
    /*    5440 */ { 0.7698, 1.0000, 1.0000 }, 
    /*    5450 */ { 0.7690, 1.0000, 1.0000 }, 
    /*    5460 */ { 0.7682, 1.0000, 1.0000 }, 
    /*    5470 */ { 0.7674, 1.0000, 1.0000 }, 
    /*    5480 */ { 0.7666, 1.0000, 1.0000 }, 
    /*    5490 */ { 0.7658, 1.0000, 1.0000 }, 
    /*    5500 */ { 0.7650, 1.0000, 1.0000 }, 
    /*    5510 */ { 0.7642, 1.0000, 1.0000 }, 
    /*    5520 */ { 0.7634, 1.0000, 1.0000 }, 
    /*    5530 */ { 0.7627, 1.0000, 1.0000 }, 
    /*    5540 */ { 0.7619, 1.0000, 1.0000 }, 
    /*    5550 */ { 0.7611, 1.0000, 1.0000 }, 
    /*    5560 */ { 0.7603, 1.0000, 1.0000 }, 
    /*    5570 */ { 0.7596, 1.0000, 1.0000 }, 
    /*    5580 */ { 0.7588, 1.0000, 1.0000 }, 
    /*    5590 */ { 0.7580, 1.0000, 1.0000 }, 
    /*    5600 */ { 0.7573, 1.0000, 1.0000 }, 
    /*    5610 */ { 0.7565, 1.0000, 1.0000 }, 
    /*    5620 */ { 0.7558, 1.0000, 1.0000 }, 
    /*    5630 */ { 0.7550, 1.0000, 1.0000 }, 
    /*    5640 */ { 0.7543, 1.0000, 1.0000 }, 
    /*    5650 */ { 0.7535, 1.0000, 1.0000 }, 
    /*    5660 */ { 0.7528, 1.0000, 1.0000 }, 
    /*    5670 */ { 0.7521, 1.0000, 1.0000 }, 
    /*    5680 */ { 0.7513, 1.0000, 1.0000 }, 
    /*    5690 */ { 0.7506, 1.0000, 1.0000 }, 
    /*    5700 */ { 0.7499, 1.0000, 1.0000 }, 
    /*    5710 */ { 0.7492, 1.0000, 1.0000 }, 
    /*    5720 */ { 0.7484, 1.0000, 1.0000 }, 
    /*    5730 */ { 0.7477, 1.0000, 1.0000 }, 
    /*    5740 */ { 0.7470, 1.0000, 1.0000 }, 
    /*    5750 */ { 0.7456, 1.0000, 1.0000 }, 
    /*    5760 */ { 0.7436, 1.0000, 1.0000 }, 
    /*    5770 */ { 0.7416, 1.0000, 1.0000 }, 
    /*    5780 */ { 0.7396, 1.0000, 1.0000 }, 
    /*    5790 */ { 0.7377, 1.0000, 1.0000 }, 
    /*    5800 */ { 0.7358, 1.0000, 1.0000 }, 
    /*    5810 */ { 0.7338, 1.0000, 1.0000 }, 
    /*    5820 */ { 0.7319, 1.0000, 1.0000 }, 
    /*    5830 */ { 0.7300, 1.0000, 1.0000 }, 
    /*    5840 */ { 0.7281, 1.0000, 1.0000 }, 
    /*    5850 */ { 0.7263, 1.0000, 1.0000 }, 
    /*    5860 */ { 0.7244, 1.0000, 1.0000 }, 
    /*    5870 */ { 0.7225, 1.0000, 1.0000 }, 
    /*    5880 */ { 0.7207, 1.0000, 1.0000 }, 
    /*    5890 */ { 0.7189, 1.0000, 1.0000 }, 
    /*    5900 */ { 0.7170, 1.0000, 1.0000 }, 
    /*    5910 */ { 0.7152, 1.0000, 1.0000 }, 
    /*    5920 */ { 0.7134, 1.0000, 1.0000 }, 
    /*    5930 */ { 0.7116, 1.0000, 1.0000 }, 
    /*    5940 */ { 0.7099, 1.0000, 1.0000 }, 
    /*    5950 */ { 0.7081, 1.0000, 1.0000 }, 
    /*    5960 */ { 0.7063, 1.0000, 1.0000 }, 
    /*    5970 */ { 0.7046, 1.0000, 1.0000 }, 
    /*    5980 */ { 0.7029, 1.0000, 1.0000 }, 
    /*    5990 */ { 0.7011, 1.0000, 1.0000 }, 
    /*    6000 */ { 0.6994, 1.0000, 1.0000 }, 
    /*    6010 */ { 0.6977, 1.0000, 1.0000 }, 
    /*    6020 */ { 0.6960, 1.0000, 1.0000 }, 
    /*    6030 */ { 0.6943, 1.0000, 1.0000 }, 
    /*    6040 */ { 0.6926, 1.0000, 1.0000 }, 
    /*    6050 */ { 0.6910, 1.0000, 1.0000 }, 
    /*    6060 */ { 0.6893, 1.0000, 1.0000 }, 
    /*    6070 */ { 0.6877, 1.0000, 1.0000 }, 
    /*    6080 */ { 0.6860, 1.0000, 1.0000 }, 
    /*    6090 */ { 0.6844, 1.0000, 1.0000 }, 
    /*    6100 */ { 0.6828, 1.0000, 1.0000 }, 
    /*    6110 */ { 0.6812, 1.0000, 1.0000 }, 
    /*    6120 */ { 0.6796, 1.0000, 1.0000 }, 
    /*    6130 */ { 0.6780, 1.0000, 1.0000 }, 
    /*    6140 */ { 0.6764, 1.0000, 1.0000 }, 
    /*    6150 */ { 0.6748, 1.0000, 1.0000 }, 
    /*    6160 */ { 0.6733, 1.0000, 1.0000 }, 
    /*    6170 */ { 0.6717, 1.0000, 1.0000 }, 
    /*    6180 */ { 0.6702, 1.0000, 1.0000 }, 
    /*    6190 */ { 0.6686, 1.0000, 1.0000 }, 
    /*    6200 */ { 0.6671, 1.0000, 1.0000 }, 
    /*    6210 */ { 0.6656, 1.0000, 1.0000 }, 
    /*    6220 */ { 0.6641, 1.0000, 1.0000 }, 
    /*    6230 */ { 0.6626, 1.0000, 1.0000 }, 
    /*    6240 */ { 0.6611, 1.0000, 1.0000 }, 
    /*    6250 */ { 0.6596, 1.0000, 1.0000 }, 
    /*    6260 */ { 0.6581, 1.0000, 1.0000 }, 
    /*    6270 */ { 0.6566, 1.0000, 1.0000 }, 
    /*    6280 */ { 0.6552, 1.0000, 1.0000 }, 
    /*    6290 */ { 0.6537, 1.0000, 1.0000 }, 
    /*    6300 */ { 0.6523, 1.0000, 1.0000 }, 
    /*    6310 */ { 0.6508, 1.0000, 1.0000 }, 
    /*    6320 */ { 0.6494, 1.0000, 1.0000 }, 
    /*    6330 */ { 0.6480, 1.0000, 1.0000 }, 
    /*    6340 */ { 0.6465, 1.0000, 1.0000 }, 
    /*    6350 */ { 0.6451, 1.0000, 1.0000 }, 
    /*    6360 */ { 0.6437, 1.0000, 1.0000 }, 
    /*    6370 */ { 0.6423, 1.0000, 1.0000 }, 
    /*    6380 */ { 0.6410, 1.0000, 1.0000 }, 
    /*    6390 */ { 0.6396, 1.0000, 1.0000 }, 
    /*    6400 */ { 0.6382, 1.0000, 1.0000 }, 
    /*    6410 */ { 0.6368, 1.0000, 1.0000 }, 
    /*    6420 */ { 0.6355, 1.0000, 1.0000 }, 
    /*    6430 */ { 0.6341, 1.0000, 1.0000 }, 
    /*    6440 */ { 0.6328, 1.0000, 1.0000 }, 
    /*    6450 */ { 0.6315, 1.0000, 1.0000 }, 
    /*    6460 */ { 0.6301, 1.0000, 1.0000 }, 
    /*    6470 */ { 0.6288, 1.0000, 1.0000 }, 
    /*    6480 */ { 0.6275, 1.0000, 1.0000 }, 
    /*    6490 */ { 0.6262, 1.0000, 1.0000 }, 
    /*    6500 */ { 0.6249, 1.0000, 1.0000 }, 
    /*    6510 */ { 0.6236, 1.0000, 1.0000 }, 
    /*    6520 */ { 0.6223, 1.0000, 1.0000 }, 
    /*    6530 */ { 0.6210, 1.0000, 1.0000 }, 
    /*    6540 */ { 0.6198, 1.0000, 1.0000 }, 
    /*    6550 */ { 0.6185, 1.0000, 1.0000 }, 
    /*    6560 */ { 0.6173, 1.0000, 1.0000 }, 
    /*    6570 */ { 0.6160, 1.0000, 1.0000 }, 
    /*    6580 */ { 0.6148, 1.0000, 1.0000 }, 
    /*    6590 */ { 0.6135, 1.0000, 1.0000 }, 
    /*    6600 */ { 0.6123, 1.0000, 1.0000 }, 
    /*    6610 */ { 0.6111, 1.0000, 1.0000 }, 
    /*    6620 */ { 0.6098, 1.0000, 1.0000 }, 
    /*    6630 */ { 0.6086, 1.0000, 1.0000 }, 
    /*    6640 */ { 0.6074, 1.0000, 1.0000 }, 
    /*    6650 */ { 0.6062, 1.0000, 1.0000 }, 
    /*    6660 */ { 0.6050, 1.0000, 1.0000 }, 
    /*    6670 */ { 0.6038, 1.0000, 1.0000 }, 
    /*    6680 */ { 0.6026, 1.0000, 1.0000 }, 
    /*    6690 */ { 0.6015, 1.0000, 1.0000 }, 
    /*    6700 */ { 0.6003, 1.0000, 1.0000 }, 
    /*    6710 */ { 0.5991, 1.0000, 1.0000 }, 
    /*    6720 */ { 0.5980, 1.0000, 1.0000 }, 
    /*    6730 */ { 0.5968, 1.0000, 1.0000 }, 
    /*    6740 */ { 0.5957, 1.0000, 1.0000 }, 
    /*    6750 */ { 0.5945, 1.0000, 1.0000 }, 
    /*    6760 */ { 0.5934, 1.0000, 1.0000 }, 
    /*    6770 */ { 0.5923, 1.0000, 1.0000 }, 
    /*    6780 */ { 0.5911, 1.0000, 1.0000 }, 
    /*    6790 */ { 0.5900, 0.9992, 1.0000 }, 
    /*    6800 */ { 0.5889, 0.9981, 1.0000 }, 
    /*    6810 */ { 0.5878, 0.9970, 1.0000 }, 
    /*    6820 */ { 0.5867, 0.9959, 1.0000 }, 
    /*    6830 */ { 0.5856, 0.9948, 1.0000 }, 
    /*    6840 */ { 0.5845, 0.9937, 1.0000 }, 
    /*    6850 */ { 0.5834, 0.9926, 1.0000 }, 
    /*    6860 */ { 0.5823, 0.9915, 1.0000 }, 
    /*    6870 */ { 0.5813, 0.9904, 1.0000 }, 
    /*    6880 */ { 0.5802, 0.9893, 1.0000 }, 
    /*    6890 */ { 0.5791, 0.9882, 1.0000 }, 
    /*    6900 */ { 0.5781, 0.9871, 1.0000 }, 
    /*    6910 */ { 0.5770, 0.9861, 1.0000 }, 
    /*    6920 */ { 0.5760, 0.9850, 1.0000 }, 
    /*    6930 */ { 0.5749, 0.9839, 1.0000 }, 
    /*    6940 */ { 0.5739, 0.9829, 1.0000 }, 
    /*    6950 */ { 0.5728, 0.9818, 1.0000 }, 
    /*    6960 */ { 0.5718, 0.9808, 1.0000 }, 
    /*    6970 */ { 0.5708, 0.9797, 1.0000 }, 
    /*    6980 */ { 0.5698, 0.9787, 1.0000 }, 
    /*    6990 */ { 0.5687, 0.9776, 1.0000 }, 
    /*    7000 */ { 0.5677, 0.9766, 1.0000 }, 
};

}  // NameSpace Digikam

#endif /* BLACKBODY_H */
