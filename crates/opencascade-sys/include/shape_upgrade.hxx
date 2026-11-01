#include <ShapeUpgrade_UnifySameDomain.hxx>
#include <ShapeUpgrade_RemoveInternalWires.hxx>
#include <Standard_Failure.hxx>
#include <TopoDS_Shape.hxx>
#include <bindings_common.hxx>
#include <stdexcept>

inline void shape_upgrade_rethrow(const Standard_Failure &e) {
  const char *msg = e.GetMessageString();
  throw std::runtime_error(msg ? msg : "OpenCASCADE Standard_Failure");
}

inline std::unique_ptr<ShapeUpgrade_RemoveInternalWires>
RemoveInternalWires_new(const TopoDS_Shape &shape) {
  try {
    return std::unique_ptr<ShapeUpgrade_RemoveInternalWires>(
        new ShapeUpgrade_RemoveInternalWires(shape));
  } catch (const Standard_Failure &e) {
    shape_upgrade_rethrow(e);
    return nullptr;
  }
}

inline void RemoveInternalWires_set_min_area(ShapeUpgrade_RemoveInternalWires &fix,
                                             Standard_Real value) {
  fix.MinArea() = value;
}

inline Standard_Boolean RemoveInternalWires_Perform(ShapeUpgrade_RemoveInternalWires &fix) {
  try {
    return fix.Perform();
  } catch (const Standard_Failure &e) {
    shape_upgrade_rethrow(e);
    return false;
  }
}

inline std::unique_ptr<TopoDS_Shape>
RemoveInternalWires_GetResult(const ShapeUpgrade_RemoveInternalWires &fix) {
  try {
    return std::unique_ptr<TopoDS_Shape>(new TopoDS_Shape(fix.GetResult()));
  } catch (const Standard_Failure &e) {
    shape_upgrade_rethrow(e);
    return nullptr;
  }
}
