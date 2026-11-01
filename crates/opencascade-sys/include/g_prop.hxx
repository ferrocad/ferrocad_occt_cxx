#include <GProp_GProps.hxx>
#include <GProp_PrincipalProps.hxx>
#include <bindings_common.hxx>
#include <gp_Mat.hxx>
#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>

inline std::unique_ptr<gp_Pnt> GProp_GProps_CentreOfMass(const GProp_GProps &props) {
  return std::unique_ptr<gp_Pnt>(new gp_Pnt(props.CentreOfMass()));
}

inline std::unique_ptr<gp_Mat> GProp_GProps_MatrixOfInertia(const GProp_GProps &props) {
  return std::unique_ptr<gp_Mat>(new gp_Mat(props.MatrixOfInertia()));
}

inline std::unique_ptr<GProp_PrincipalProps> GProp_GProps_PrincipalProperties(const GProp_GProps &props) {
  return std::unique_ptr<GProp_PrincipalProps>(new GProp_PrincipalProps(props.PrincipalProperties()));
}
