#include <BRepTools.hxx>
#include <BRep_Builder.hxx>
#include <TopoDS_Wire.hxx>
#include <bindings_common.hxx>

#include <sstream>
#include <string>

inline std::unique_ptr<TopoDS_Wire> outer_wire(const TopoDS_Face &face) {
  return std::unique_ptr<TopoDS_Wire>(new TopoDS_Wire(BRepTools::OuterWire(face)));
}

inline bool write_brep_text(const TopoDS_Shape &shape, rust::String path) {
  return BRepTools::Write(shape, path.c_str());
}

inline std::unique_ptr<TopoDS_Shape> read_brep_text(rust::String path) {
  BRep_Builder builder;
  auto shape = std::unique_ptr<TopoDS_Shape>(new TopoDS_Shape());

  if (BRepTools::Read(*shape, path.c_str(), builder)) {
    return shape;
  } else {
    return std::unique_ptr<TopoDS_Shape>(nullptr);
  }
}

inline void write_brep_bytes(const TopoDS_Shape &shape, rust::Vec<uint8_t> &out) {
  std::ostringstream stream;
  BRepTools::Write(shape, stream);
  const std::string bytes = stream.str();
  for (char c : bytes)
    out.push_back(static_cast<uint8_t>(c));
}

inline std::unique_ptr<TopoDS_Shape> read_brep_bytes(rust::Slice<const uint8_t> data) {
  const std::string bytes(reinterpret_cast<const char *>(data.data()), data.size());
  std::istringstream stream(bytes);
  auto shape = std::unique_ptr<TopoDS_Shape>(new TopoDS_Shape());
  BRep_Builder builder;
  BRepTools::Read(*shape, stream, builder);
  if (shape->IsNull())
    return nullptr;
  return shape;
}
