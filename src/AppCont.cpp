/*
This file is part of pyOCCT which provides Python bindings to the OpenCASCADE
geometry kernel.

Copyright (C) 2016-2018  Laughlin Research, LLC (info@laughlinresearch.com)

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include <pyOCCT_Common.hpp>

#include <AppCont_ContMatrices.hxx>
#include <Standard_TypeDef.hxx>
#include <math_Matrix.hxx>
#include <NCollection_Array1.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_Pnt.hxx>
#include <gp_Vec2d.hxx>
#include <gp_Vec.hxx>
#include <AppCont_Function.hxx>
#include <AppCont_LeastSquare.hxx>
#include <AppParCurves_Constraint.hxx>
#include <AppParCurves_MultiCurve.hxx>

PYBIND11_MODULE(AppCont, mod) {

	// IMPORT
	py::module::import("OCCT.Standard");
	py::module::import("OCCT.math");
	py::module::import("OCCT.NCollection");
	py::module::import("OCCT.gp");
	py::module::import("OCCT.AppParCurves");

	py::module other_mod;

	// IMPORT GUARDS

	// ENUMS

	// FUNCTIONS
	// C:\Miniconda\envs\occt\Library\include\opencascade\AppCont_ContMatrices.hxx
	mod.def("InvMMatrix", (void (*)(const Standard_Integer, math_Matrix &)) &InvMMatrix, "None", py::arg("classe"), py::arg("M"));

	// C:\Miniconda\envs\occt\Library\include\opencascade\AppCont_ContMatrices.hxx
	mod.def("MMatrix", (void (*)(const Standard_Integer, math_Matrix &)) &MMatrix, "None", py::arg("classe"), py::arg("M"));

	// C:\Miniconda\envs\occt\Library\include\opencascade\AppCont_ContMatrices.hxx
	mod.def("IBPMatrix", (void (*)(const Standard_Integer, math_Matrix &)) &IBPMatrix, "None", py::arg("classe"), py::arg("M"));

	// C:\Miniconda\envs\occt\Library\include\opencascade\AppCont_ContMatrices.hxx
	mod.def("IBTMatrix", (void (*)(const Standard_Integer, math_Matrix &)) &IBTMatrix, "None", py::arg("classe"), py::arg("M"));

	// C:\Miniconda\envs\occt\Library\include\opencascade\AppCont_ContMatrices.hxx
	mod.def("VBernstein", (void (*)(const Standard_Integer, const Standard_Integer, math_Matrix &)) &VBernstein, "None", py::arg("classe"), py::arg("nbpoints"), py::arg("M"));


	// CLASSES
	// Callback for AppCont_Function.
	class PyCallback_AppCont_Function : public AppCont_Function {
	public:
		using AppCont_Function::AppCont_Function;

		Standard_Real FirstParameter() const  override { PYBIND11_OVERLOAD_PURE(Standard_Real, AppCont_Function, FirstParameter, ); }
		Standard_Real LastParameter() const  override { PYBIND11_OVERLOAD_PURE(Standard_Real, AppCont_Function, LastParameter, ); }
		Standard_Boolean Value(const Standard_Real theU, NCollection_Array1<gp_Pnt2d> & thePnt2d, NCollection_Array1<gp_Pnt> & thePnt) const  override { PYBIND11_OVERLOAD_PURE(Standard_Boolean, AppCont_Function, Value, theU, thePnt2d, thePnt); }
		Standard_Boolean D1(const Standard_Real theU, NCollection_Array1<gp_Vec2d> & theVec2d, NCollection_Array1<gp_Vec> & theVec) const  override { PYBIND11_OVERLOAD_PURE(Standard_Boolean, AppCont_Function, D1, theU, theVec2d, theVec); }
	};

	// C:\Miniconda\envs\occt\Library\include\opencascade\AppCont_Function.hxx
	py::class_<AppCont_Function, std::unique_ptr<AppCont_Function, Deleter<AppCont_Function>>, PyCallback_AppCont_Function> cls_AppCont_Function(mod, "AppCont_Function", "Class describing a continous 3d and/or function f(u). This class must be provided by the user to use the approximation algorithm FittingCurve.");
	cls_AppCont_Function.def(py::init<>());
	cls_AppCont_Function.def("GetNumberOfPoints", [](AppCont_Function &self, Standard_Integer & theNbPnt, Standard_Integer & theNbPnt2d){ self.GetNumberOfPoints(theNbPnt, theNbPnt2d); return std::tuple<Standard_Integer &, Standard_Integer &>(theNbPnt, theNbPnt2d); }, "Get number of 3d and 2d points returned by 'Value' and 'D1' functions.", py::arg("theNbPnt"), py::arg("theNbPnt2d"));
	cls_AppCont_Function.def("GetNbOf3dPoints", (Standard_Integer (AppCont_Function::*)() const ) &AppCont_Function::GetNbOf3dPoints, "Get number of 3d points returned by 'Value' and 'D1' functions.");
	cls_AppCont_Function.def("GetNbOf2dPoints", (Standard_Integer (AppCont_Function::*)() const ) &AppCont_Function::GetNbOf2dPoints, "Get number of 2d points returned by 'Value' and 'D1' functions.");
	cls_AppCont_Function.def("FirstParameter", (Standard_Real (AppCont_Function::*)() const ) &AppCont_Function::FirstParameter, "Returns the first parameter of the function.");
	cls_AppCont_Function.def("LastParameter", (Standard_Real (AppCont_Function::*)() const ) &AppCont_Function::LastParameter, "Returns the last parameter of the function.");
	cls_AppCont_Function.def("Value", (Standard_Boolean (AppCont_Function::*)(const Standard_Real, NCollection_Array1<gp_Pnt2d> &, NCollection_Array1<gp_Pnt> &) const ) &AppCont_Function::Value, "Returns the point at parameter <theU>.", py::arg("theU"), py::arg("thePnt2d"), py::arg("thePnt"));
	cls_AppCont_Function.def("D1", (Standard_Boolean (AppCont_Function::*)(const Standard_Real, NCollection_Array1<gp_Vec2d> &, NCollection_Array1<gp_Vec> &) const ) &AppCont_Function::D1, "Returns the derivative at parameter <theU>.", py::arg("theU"), py::arg("theVec2d"), py::arg("theVec"));
	cls_AppCont_Function.def("PeriodInformation", [](AppCont_Function &self, const Standard_Integer a0, Standard_Boolean & IsPeriodic, Standard_Real & thePeriod){ self.PeriodInformation(a0, IsPeriodic, thePeriod); return std::tuple<Standard_Boolean &, Standard_Real &>(IsPeriodic, thePeriod); }, "Return information about peridicity in output paramateters space.", py::arg(""), py::arg("IsPeriodic"), py::arg("thePeriod"));

	// C:\Miniconda\envs\occt\Library\include\opencascade\AppCont_LeastSquare.hxx
	py::class_<PeriodicityInfo, std::unique_ptr<PeriodicityInfo, Deleter<PeriodicityInfo>>> cls_PeriodicityInfo(mod, "PeriodicityInfo", "None");
	cls_PeriodicityInfo.def(py::init<>());

	// C:\Miniconda\envs\occt\Library\include\opencascade\AppCont_LeastSquare.hxx
	py::class_<AppCont_LeastSquare, std::unique_ptr<AppCont_LeastSquare, Deleter<AppCont_LeastSquare>>> cls_AppCont_LeastSquare(mod, "AppCont_LeastSquare", "None");
	cls_AppCont_LeastSquare.def(py::init<const AppCont_Function &, const Standard_Real, const Standard_Real, const AppParCurves_Constraint, const AppParCurves_Constraint, const Standard_Integer, const Standard_Integer>(), py::arg("SSP"), py::arg("U0"), py::arg("U1"), py::arg("FirstCons"), py::arg("LastCons"), py::arg("Deg"), py::arg("NbPoints"));
	cls_AppCont_LeastSquare.def("Value", (const AppParCurves_MultiCurve & (AppCont_LeastSquare::*)()) &AppCont_LeastSquare::Value, "None");
	cls_AppCont_LeastSquare.def("Error", [](AppCont_LeastSquare &self, Standard_Real & F, Standard_Real & MaxE3d, Standard_Real & MaxE2d){ self.Error(F, MaxE3d, MaxE2d); return std::tuple<Standard_Real &, Standard_Real &, Standard_Real &>(F, MaxE3d, MaxE2d); }, "None", py::arg("F"), py::arg("MaxE3d"), py::arg("MaxE2d"));
	cls_AppCont_LeastSquare.def("IsDone", (Standard_Boolean (AppCont_LeastSquare::*)() const ) &AppCont_LeastSquare::IsDone, "None");


}
