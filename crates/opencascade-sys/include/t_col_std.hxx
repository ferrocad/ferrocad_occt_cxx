#include <TColStd_Array1OfInteger.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array2OfReal.hxx>
#include <bindings_common.hxx>

inline double TColStd_Array1OfReal_Value(const TColStd_Array1OfReal &array, Standard_Integer index) {
  return array.Value(index);
}

inline Standard_Integer TColStd_Array1OfInteger_Value(const TColStd_Array1OfInteger &array,
                                                      Standard_Integer index) {
  return array.Value(index);
}

inline double TColStd_Array2OfReal_Value(const TColStd_Array2OfReal &array, Standard_Integer row,
                                         Standard_Integer column) {
  return array.Value(row, column);
}

inline void TColStd_Array1OfReal_SetValue(TColStd_Array1OfReal &array, Standard_Integer index,
                                          double value) {
  array.SetValue(index, value);
}

inline void TColStd_Array1OfInteger_SetValue(TColStd_Array1OfInteger &array, Standard_Integer index,
                                             Standard_Integer value) {
  array.SetValue(index, value);
}

inline void TColStd_Array2OfReal_SetValue(TColStd_Array2OfReal &array, Standard_Integer row,
                                          Standard_Integer column, double value) {
  array.SetValue(row, column, value);
}
