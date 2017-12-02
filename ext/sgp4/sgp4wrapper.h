// C++ wrappers to call the off-the-shelf SGP4 functions from C.
#ifdef __cplusplus
extern "C" {
#endif

#include <sgp4types.h>

  extern void invjday_c(
    double jd,
    int *year, int *mon, int *day,
    int *hr, int *minute, double *sec
  );

  extern int sgp4_c(
     gravconsttype whichconst, elsetrec* satrec,  double tsince,
     double r[3],  double v[3]
    );

  extern void twoline2rv_c(
    char      longstr1[130], char longstr2[130],
    char      typerun,  char typeinput, char opsmode,
    gravconsttype       whichconst,
    double* startmfe, double* stopmfe, double* deltamin,
    elsetrec* satrec
    );
#ifdef __cplusplus
}
#endif
