#include <TopTools_HSequenceOfShape.hxx>
#include <TopTools_IndexedDataMapOfShapeListOfShape.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopTools_ListOfShape.hxx>
#include <TopoDS_Face.hxx>
#include <bindings_common.hxx>

// MSVC only: same reasoning
// as Handle_Poly_Triangulation_deref in poly.hxx.
inline const TopTools_HSequenceOfShape &
Handle_TopTools_HSequenceOfShape_deref(const Handle_TopTools_HSequenceOfShape &handle) {
  return handle_try_deref<TopTools_HSequenceOfShape>(handle);
}

inline std::unique_ptr<Handle_TopTools_HSequenceOfShape> new_Handle_TopTools_HSequenceOfShape() {
  auto sequence = new TopTools_HSequenceOfShape();
  auto handle = new Handle_TopTools_HSequenceOfShape(sequence);

  return std::unique_ptr<Handle_TopTools_HSequenceOfShape>(handle);
}

inline void TopTools_HSequenceOfShape_append(Handle_TopTools_HSequenceOfShape &handle, const TopoDS_Shape &shape) {
  handle->Append(shape);
}

inline Standard_Integer TopTools_HSequenceOfShape_length(const Handle_TopTools_HSequenceOfShape &handle) {
  return handle->Length();
}

inline const TopoDS_Shape &TopTools_HSequenceOfShape_value(const Handle_TopTools_HSequenceOfShape &handle,
                                                           Standard_Integer index) {
  return handle->Value(index);
}

// `Clear` takes an optional allocator parameter in NCollection, so cxx cannot
// take the member address; the default-allocator form is what callers want.
inline void list_clear(TopTools_ListOfShape &list) { list.Clear(); }

// OCCT 8 changed `NCollection_List::Size()` from `Standard_Integer` to
// `size_t`, and cxx binds a member through an exact-type member pointer, so a
// direct binding compiles on 7.8 or on 8.x but not on both. `Extent()` is the
// legacy int API and is unchanged; this wrapper keeps the `Size` capability
// available with one signature on every OCCT.
inline int list_size(const TopTools_ListOfShape &list) {
  return static_cast<int>(list.Size());
}

inline void map_clear(TopTools_IndexedMapOfShape &map) { map.Clear(); }
