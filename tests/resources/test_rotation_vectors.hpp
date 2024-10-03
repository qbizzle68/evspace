#ifndef _VECTOR_TEST_RESOURCE_H_
#define _VECTOR_TEST_RESOURCE_H_

/*
 *  The following vector were computed with:
 *      axis rotation angles are 0.7853981633974483
 *      euler rotation angles are [0.523599, 0.785398, 1.047198]
 *      euler from-to rotations are from [0.000000, 0.785398, 1.570796] to [0.523599, 0.785398, 1.047198]
 *      offset vector is [10, 20, 30]
 *      offset from vector is [10, 20, 30]
 *      offset to vector is [100, 200, 300]
 *      test vector is [1, 2, 3]
 */

// single axis rotation vectors
#define X_AXIS_ROTATION_TO { 1.0, 3.5355339059327378, 0.7071067811865477 }
#define Y_AXIS_ROTATION_TO { -1.4142135623730954, 2.0, 2.8284271247461903 }
#define Z_AXIS_ROTATION_TO { 2.121320343559643, 0.7071067811865476, 3.0 }
#define X_AXIS_ROTATION_FROM { 1.0, -0.7071067811865477, 3.5355339059327378 }
#define Y_AXIS_ROTATION_FROM { 2.8284271247461903, 2.0, 1.4142135623730954 }
#define Z_AXIS_ROTATION_FROM { -0.7071067811865476, 2.121320343559643, 3.0 }
#define X_AXIS_ROTATION_OFFSET_TO { -9.0, -31.81980515339464, -6.363961030678928 }
#define Y_AXIS_ROTATION_OFFSET_TO { 12.727922061357855, -18.0, -25.455844122715714 }
#define Z_AXIS_ROTATION_OFFSET_TO { -19.091883092036785, -6.3639610306789285, -27.0 }
#define X_AXIS_ROTATION_OFFSET_FROM { 11.0, 19.292893218813454, 33.53553390593274 }
#define Y_AXIS_ROTATION_OFFSET_FROM { 12.82842712474619, 22.0, 31.414213562373096 }
#define Z_AXIS_ROTATION_OFFSET_FROM { 9.292893218813452, 22.121320343559642, 33.0 }

// euler rotation vectors
#define XYZ_ROTATION_TO { 2.587586233319513, 1.9822707900625822, 1.8371173070873836 }
#define XZY_ROTATION_TO { 0.1122813159634175, 1.578298261984863, 3.390629366695966 }
#define XYX_ROTATION_TO { -0.4229037447142887, 3.2070156614541716, -1.8804794521329657 }
#define ZXZ_ROTATION_TO { 3.5246039629115273, -0.11976949160545924, 1.2501288627613274 }
#define XYZ_ROTATION_FROM { 1.2501288627613274, 0.11976949160546013, 3.524603962911527 }
#define XZY_ROTATION_FROM { 0.7764571353075622, 2.804934048801438, 2.3514802357035345 }
#define XYX_ROTATION_FROM { 2.9925118243579583, -2.1731237272079924, 0.5678082839510612 }
#define ZXZ_ROTATION_FROM { -0.6660667347691303, -1.3104401892861168, 3.440799560441985 }
#define XYZ_ROTATION_OFFSET_TO { -23.28827609987562, -17.840437110563236, -16.534055763786455 }
#define XZY_ROTATION_OFFSET_TO { -1.0105318436707584, -14.204684357863766, -30.515664300263698 }
#define XYX_ROTATION_OFFSET_TO { 3.8061337024285997, -28.86314095308754, 16.92431506919669 }
#define ZXZ_ROTATION_OFFSET_TO { -31.721435666203746, 1.0779254244491323, -11.251159764851945 }
#define XYZ_ROTATION_OFFSET_FROM { 11.250128862761327, 20.11976949160546, 33.52460396291153 }
#define XZY_ROTATION_OFFSET_FROM { 10.776457135307563, 22.80493404880144, 32.351480235703534 }
#define XYX_ROTATION_OFFSET_FROM { 12.992511824357958, 17.826876272792006, 30.56780828395106 }
#define ZXZ_ROTATION_OFFSET_FROM { 9.33393326523087, 18.689559810713885, 33.44079956044199 }

// euler from to rotation vectors
#define FROM_XYZ_TO_YXY_ROTATION { -2.4075815434782335, 2.5769611828652055, 1.2501288627613274 }
#define FROM_XZY_TO_XYX_ROTATION { -1.1137095148154526, 2.2117857261687686, -2.804934048801438 }
#define FROM_XYX_TO_ZYX_ROTATION { 1.714524315788747, 2.517526491780131, 2.1731237272079924 }
#define FROM_ZXZ_TO_YZY_ROTATION { -3.4407995604419854, -0.45564083930556243, -1.3976014490616298 }
#define FROM_OFFSET_XYZ_TO_YXY_ROTATION { -9.478649355343709, 37.93230024219258, 11.25012886276133 }
#define FROM_OFFSET_XZY_TO_XYX_ROTATION { -15.255845138546402, 30.496056973630672, -22.80493404880144 }
#define FROM_OFFSET_XYX_TO_ZYX_ROTATION { -12.427611307942202, 30.801797739242033, -17.826876272792006 }
#define FROM_OFFSET_ZXZ_TO_YZY_ROTATION { -33.44079956044199, 6.615426972559913, 19.8156019865348 }
#define FROM_XYZ_TO_OFFSET_YXY_ROTATION { 68.30309657517657, -350.9764294104086, -98.74987113723867 }
#define FROM_XZY_TO_OFFSET_XYX_ROTATION { 140.30764672249404, -280.63092674845024, 197.19506595119856 }
#define FROM_XYX_TO_OFFSET_ZYX_ROTATION { 143.13588055309822, -280.3251859828389, 202.17312372720798 }
#define FROM_ZXZ_TO_OFFSET_YZY_ROTATION { 296.559200439558, -71.16631895796031, -213.52963580502595 }
#define FROM_OFFSET_XYZ_TO_OFFSET_YXY_ROTATION { 61.23202876331102, -315.6210903510812, -88.74987113723867 }
#define FROM_OFFSET_XZY_TO_OFFSET_XYX_ROTATION { 126.16551109876309, -252.34665550098833, 177.19506595119856 }
#define FROM_OFFSET_XYX_TO_OFFSET_ZYX_ROTATION { 128.9937449293673, -252.040914735377, 182.173123727208 }
#define FROM_OFFSET_ZXZ_TO_OFFSET_YZY_ROTATION { 266.559200439558, -64.09525114609484, -192.31643236942952 }

#endif  // _VECTOR_TEST_RESOURCE_H_