#include <BRepLProp_CLProps.hxx>
#include <BRepLProp_SLProps.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <BRepAdaptor_Surface.hxx>
#include <Standard_Failure.hxx>
#include <gp_Dir.hxx>
#include <gp_Vec.hxx>
#include <bindings_common.hxx>
#include <stdexcept>

inline void b_rep_l_prop_rethrow(const Standard_Failure &e) {
  const char *msg = e.GetMessageString();
  throw std::runtime_error(msg ? msg : "OpenCASCADE Standard_Failure");
}

inline std::unique_ptr<BRepLProp_CLProps>
BRepLProp_CLProps_new(const BRepAdaptor_Curve &curve, double u, int n, double resolution) {
  try {
    return std::unique_ptr<BRepLProp_CLProps>(new BRepLProp_CLProps(curve, u, n, resolution));
  } catch (const Standard_Failure &e) {
    b_rep_l_prop_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<gp_Dir> CLProps_Normal(BRepLProp_CLProps &props) {
  try {
    gp_Dir d;
    props.Normal(d);
    return std::unique_ptr<gp_Dir>(new gp_Dir(d));
  } catch (const Standard_Failure &e) {
    b_rep_l_prop_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<gp_Vec> CLProps_D1(BRepLProp_CLProps &props) {
  try {
    return std::unique_ptr<gp_Vec>(new gp_Vec(props.D1()));
  } catch (const Standard_Failure &e) {
    b_rep_l_prop_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<gp_Vec> CLProps_D2(BRepLProp_CLProps &props) {
  try {
    return std::unique_ptr<gp_Vec>(new gp_Vec(props.D2()));
  } catch (const Standard_Failure &e) {
    b_rep_l_prop_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<gp_Vec> CLProps_D3(BRepLProp_CLProps &props) {
  try {
    return std::unique_ptr<gp_Vec>(new gp_Vec(props.D3()));
  } catch (const Standard_Failure &e) {
    b_rep_l_prop_rethrow(e);
    return nullptr;
  }
}

inline double CLProps_Curvature(BRepLProp_CLProps &props) {
  try {
    return props.Curvature();
  } catch (const Standard_Failure &e) {
    b_rep_l_prop_rethrow(e);
    return 0.0;
  }
}

inline std::unique_ptr<BRepLProp_SLProps>
BRepLProp_SLProps_new(const BRepAdaptor_Surface &surface, double u, double v, int n,
                      double resolution) {
  try {
    return std::unique_ptr<BRepLProp_SLProps>(new BRepLProp_SLProps(surface, u, v, n, resolution));
  } catch (const Standard_Failure &e) {
    b_rep_l_prop_rethrow(e);
    return nullptr;
  }
}

inline bool IsNormalDefined(BRepLProp_SLProps &props) { return props.IsNormalDefined(); }

inline bool IsTangentUDefined(BRepLProp_SLProps &props) { return props.IsTangentUDefined(); }

inline bool IsTangentVDefined(BRepLProp_SLProps &props) { return props.IsTangentVDefined(); }

inline bool IsCurvatureDefined(BRepLProp_SLProps &props) { return props.IsCurvatureDefined(); }

inline std::unique_ptr<gp_Dir> SLProps_Normal(BRepLProp_SLProps &props) {
  try {
    return std::unique_ptr<gp_Dir>(new gp_Dir(props.Normal()));
  } catch (const Standard_Failure &e) {
    b_rep_l_prop_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<gp_Dir> SLProps_TangentU(BRepLProp_SLProps &props) {
  try {
    gp_Dir d;
    props.TangentU(d);
    return std::unique_ptr<gp_Dir>(new gp_Dir(d));
  } catch (const Standard_Failure &e) {
    b_rep_l_prop_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<gp_Dir> SLProps_TangentV(BRepLProp_SLProps &props) {
  try {
    gp_Dir d;
    props.TangentV(d);
    return std::unique_ptr<gp_Dir>(new gp_Dir(d));
  } catch (const Standard_Failure &e) {
    b_rep_l_prop_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<gp_Vec> SLProps_D1U(BRepLProp_SLProps &props) {
  try {
    return std::unique_ptr<gp_Vec>(new gp_Vec(props.D1U()));
  } catch (const Standard_Failure &e) {
    b_rep_l_prop_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<gp_Vec> SLProps_D1V(BRepLProp_SLProps &props) {
  try {
    return std::unique_ptr<gp_Vec>(new gp_Vec(props.D1V()));
  } catch (const Standard_Failure &e) {
    b_rep_l_prop_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<gp_Vec> SLProps_D2U(BRepLProp_SLProps &props) {
  try {
    return std::unique_ptr<gp_Vec>(new gp_Vec(props.D2U()));
  } catch (const Standard_Failure &e) {
    b_rep_l_prop_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<gp_Vec> SLProps_D2V(BRepLProp_SLProps &props) {
  try {
    return std::unique_ptr<gp_Vec>(new gp_Vec(props.D2V()));
  } catch (const Standard_Failure &e) {
    b_rep_l_prop_rethrow(e);
    return nullptr;
  }
}

inline std::unique_ptr<gp_Vec> SLProps_DUV(BRepLProp_SLProps &props) {
  try {
    return std::unique_ptr<gp_Vec>(new gp_Vec(props.DUV()));
  } catch (const Standard_Failure &e) {
    b_rep_l_prop_rethrow(e);
    return nullptr;
  }
}

inline double SLProps_MinCurvature(BRepLProp_SLProps &props) {
  try {
    return props.MinCurvature();
  } catch (const Standard_Failure &e) {
    b_rep_l_prop_rethrow(e);
    return 0.0;
  }
}

inline double SLProps_MaxCurvature(BRepLProp_SLProps &props) {
  try {
    return props.MaxCurvature();
  } catch (const Standard_Failure &e) {
    b_rep_l_prop_rethrow(e);
    return 0.0;
  }
}
