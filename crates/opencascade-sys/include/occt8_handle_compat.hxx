#pragma once

// `Handle_Class` compatibility shim for OCCT 8.
//
// Up to OCCT 7.x every class header ended with `DEFINE_STANDARD_HANDLE(Class, Base)`,
// which declares the `Handle_Class` name. OCCT 8.0 dropped those calls from roughly
// 1,970 headers (see OCCT's `adm/scripts/migration_800/`), so the handle names the
// cxx bridges spell out no longer exist in C++.
//
// The Rust side declares these as opaque `type Handle_X;`, so cxx only needs a
// well-formed C++ type behind each name; it never inspects the contents. Declaring
// them as aliases of `opencascade::handle<T>` matches what `DEFINE_STANDARD_HANDLE`
// expanded to on non-MSVC compilers and what `Handle(Class)` still expands to.
//
// `Standard_Type` is deliberately NOT listed here: OCCT 8 still defines
// `Handle_Standard_Type` in `Standard_Type.hxx`, and a second declaration would clash.
//
// `TColgp_HArray1OfPnt` and `TopTools_HSequenceOfShape` are aliased through their
// underlying NCollection types rather than by including the OCCT 8
// `Deprecated/NCollectionAliases/` headers: those headers are deprecated and this
// shim must not depend on them being installed.
//
// The container typedefs (section 2) are here for the same reason and one more:
// OCCT 8 removed the forwarding headers that used to bring `TopTools_ListOfShape`
// and friends in transitively, so a bridge can name them without any include
// declaring them. Defining them from NCollection directly restores them.

#include <Standard_Version.hxx>

#if OCC_VERSION_MAJOR >= 8

#include <Geom2d_BSplineCurve.hxx>
#include <Geom2d_Curve.hxx>
#include <Geom2d_Ellipse.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom_BezierCurve.hxx>
#include <Geom_BezierSurface.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom_BSplineSurface.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Conic.hxx>
#include <Geom_ConicalSurface.hxx>
#include <Geom_Curve.hxx>
#include <Geom_CylindricalSurface.hxx>
#include <Geom_Ellipse.hxx>
#include <Geom_Hyperbola.hxx>
#include <Geom_Line.hxx>
#include <Geom_OffsetCurve.hxx>
#include <Geom_Parabola.hxx>
#include <Geom_Plane.hxx>
#include <Geom_SphericalSurface.hxx>
#include <Geom_Surface.hxx>
#include <Geom_ToroidalSurface.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <Law_Function.hxx>
#include <Poly_Triangulation.hxx>
#include <ShapeFix_Edge.hxx>
#include <ShapeFix_Face.hxx>
#include <ShapeFix_Root.hxx>
#include <ShapeFix_Shape.hxx>
#include <ShapeFix_Shell.hxx>
#include <ShapeFix_Solid.hxx>
#include <ShapeFix_Wire.hxx>
#include <NCollection_HArray1.hxx>
#include <NCollection_HSequence.hxx>
#include <Standard_Handle.hxx>
#include <TopoDS_Shape.hxx>
#include <gp_Pnt.hxx>
#include <gp_Dir.hxx>
#include <gp_Pnt2d.hxx>
#include <NCollection_Array1.hxx>
#include <NCollection_Array2.hxx>
#include <NCollection_List.hxx>
#include <NCollection_IndexedMap.hxx>
#include <NCollection_IndexedDataMap.hxx>
#include <TopTools_ShapeMapHasher.hxx>

using Handle_Geom2d_BSplineCurve = opencascade::handle<Geom2d_BSplineCurve>;
using Handle_Geom2d_Curve = opencascade::handle<Geom2d_Curve>;
using Handle_Geom2d_Ellipse = opencascade::handle<Geom2d_Ellipse>;
using Handle_Geom2d_TrimmedCurve = opencascade::handle<Geom2d_TrimmedCurve>;
using Handle_Geom_BezierCurve = opencascade::handle<Geom_BezierCurve>;
using Handle_Geom_BezierSurface = opencascade::handle<Geom_BezierSurface>;
using Handle_Geom_BSplineCurve = opencascade::handle<Geom_BSplineCurve>;
using Handle_Geom_BSplineSurface = opencascade::handle<Geom_BSplineSurface>;
using Handle_Geom_Circle = opencascade::handle<Geom_Circle>;
using Handle_Geom_Conic = opencascade::handle<Geom_Conic>;
using Handle_Geom_ConicalSurface = opencascade::handle<Geom_ConicalSurface>;
using Handle_Geom_Curve = opencascade::handle<Geom_Curve>;
using Handle_Geom_CylindricalSurface = opencascade::handle<Geom_CylindricalSurface>;
using Handle_Geom_Ellipse = opencascade::handle<Geom_Ellipse>;
using Handle_Geom_Hyperbola = opencascade::handle<Geom_Hyperbola>;
using Handle_Geom_Line = opencascade::handle<Geom_Line>;
using Handle_Geom_OffsetCurve = opencascade::handle<Geom_OffsetCurve>;
using Handle_Geom_Parabola = opencascade::handle<Geom_Parabola>;
using Handle_Geom_Plane = opencascade::handle<Geom_Plane>;
using Handle_Geom_SphericalSurface = opencascade::handle<Geom_SphericalSurface>;
using Handle_Geom_Surface = opencascade::handle<Geom_Surface>;
using Handle_Geom_ToroidalSurface = opencascade::handle<Geom_ToroidalSurface>;
using Handle_Geom_TrimmedCurve = opencascade::handle<Geom_TrimmedCurve>;
using Handle_Law_Function = opencascade::handle<Law_Function>;
using Handle_Poly_Triangulation = opencascade::handle<Poly_Triangulation>;
using Handle_ShapeFix_Edge = opencascade::handle<ShapeFix_Edge>;
using Handle_ShapeFix_Face = opencascade::handle<ShapeFix_Face>;
using Handle_ShapeFix_Root = opencascade::handle<ShapeFix_Root>;
using Handle_ShapeFix_Shape = opencascade::handle<ShapeFix_Shape>;
using Handle_ShapeFix_Shell = opencascade::handle<ShapeFix_Shell>;
using Handle_ShapeFix_Solid = opencascade::handle<ShapeFix_Solid>;
using Handle_ShapeFix_Wire = opencascade::handle<ShapeFix_Wire>;
using Handle_TColgp_HArray1OfPnt = opencascade::handle<NCollection_HArray1<gp_Pnt>>;
using Handle_TopTools_HSequenceOfShape = opencascade::handle<NCollection_HSequence<TopoDS_Shape>>;

// Container names. OCCT 8 dropped the includes that made these reachable
// transitively; the definitions are copied from the deprecated alias headers
// (`Deprecated/NCollectionAliases/`) so the types are identical.
using TColgp_HArray1OfPnt = NCollection_HArray1<gp_Pnt>;
using TopTools_HSequenceOfShape = NCollection_HSequence<TopoDS_Shape>;
using TColgp_Array1OfPnt = NCollection_Array1<gp_Pnt>;
using TColgp_Array1OfPnt2d = NCollection_Array1<gp_Pnt2d>;
using TColgp_Array1OfDir = NCollection_Array1<gp_Dir>;
using TColgp_Array2OfPnt = NCollection_Array2<gp_Pnt>;
using TColStd_Array1OfInteger = NCollection_Array1<int>;
using TColStd_Array1OfReal = NCollection_Array1<double>;
using TColStd_Array2OfReal = NCollection_Array2<double>;
using TopTools_ListOfShape = NCollection_List<TopoDS_Shape>;
using TopTools_ListIteratorOfListOfShape = NCollection_List<TopoDS_Shape>::Iterator;
using TopTools_IndexedMapOfShape = NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>;
using TopTools_IndexedDataMapOfShapeListOfShape =
  NCollection_IndexedDataMap<TopoDS_Shape, TopTools_ListOfShape, TopTools_ShapeMapHasher>;

#endif // OCC_VERSION_MAJOR >= 8
