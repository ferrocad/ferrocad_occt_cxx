#include <BRepLProp_CLProps.hxx>
#include <BRepAdaptor_Curve.hxx>
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
