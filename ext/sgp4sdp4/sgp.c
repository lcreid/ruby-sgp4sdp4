#include <sgp4sdp4.h>
#include <stdio.h>

static void params_free(double *params) {
  // puts("Freeing.");
  free(params);
  // puts("Done freeing.");
}

static VALUE allocate(VALUE self) {
  // puts("Allocating.");
  double *params = malloc(sizeof(double) * N_SAT_PARAMS);
  // puts("Returning.");
  return Data_Wrap_Struct(self, NULL, params_free, params);
}

static VALUE calculate(VALUE self, VALUE since) {
  tle_t cTle;
  double *params;
  double pos[3];
  double vel[3];
  VALUE rPos;
  VALUE rVel;

  Data_Get_Struct(self, double, params);
  get_c_tle(self, &cTle);
  // puts("ABOUT TO CALCULATE.");
  // printf("ABOUT TO CALCULATE. %f\n", NUM2DBL(since));
  SGP(NUM2DBL(since), &cTle, params, pos, vel);
  rPos = rb_obj_alloc(cSgp4sdp4_coordinates);
  rb_funcall(rPos, rb_intern("initialize"), 3, DBL2NUM(pos[0]), DBL2NUM(pos[1]), DBL2NUM(pos[2]));
  rb_iv_set(self, "@pos", rPos);
  rVel = rb_obj_alloc(cSgp4sdp4_coordinates);
  rb_funcall(rVel, rb_intern("initialize"), 3, DBL2NUM(vel[0]), DBL2NUM(vel[1]), DBL2NUM(vel[2]));
  rb_iv_set(self, "@vel", rVel);
  // puts("DONE CALCULATING.");
  return self;
}

static VALUE initialize(VALUE self, VALUE tle) {
  tle_t cTle;
  double *params;

  // puts("IN INITIALIZE");
  rb_call_super(1, &tle);
  // puts("After super.");
  // rb_iv_set(self, "@tle", tle); This is what super does.

  get_c_tle(self, &cTle);
  // puts("Getting struct.");
  Data_Get_Struct(self, double, params); // This must be a macro.
  // puts("Got struct.");
  SGP_init(params, &cTle);
  // puts("Past SGP_init.");

  return self;
}

void Init_sgp4sdp4_sgp() {
  VALUE cSgp4sdp4_sgp = rb_define_class_under(mSgp4sdp4, "Sgp", cSgp4sdp4_ephemeris);
  rb_define_alloc_func(cSgp4sdp4_sgp, allocate);
  rb_define_module_function(cSgp4sdp4_sgp, "initialize", initialize, 1);
  rb_define_method(cSgp4sdp4_sgp, "calculate", calculate, 1);
}
