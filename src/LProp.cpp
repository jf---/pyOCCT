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

#include <LProp_Status.hxx>
#include <Standard_Failure.hxx>
#include <Standard_TypeDef.hxx>
#include <Standard_SStream.hxx>
#include <Standard_Handle.hxx>
#include <LProp_BadContinuity.hxx>
#include <Standard_Type.hxx>
#include <LProp_NotDefined.hxx>
#include <LProp_CIType.hxx>
#include <NCollection_BaseSequence.hxx>
#include <NCollection_BaseAllocator.hxx>
#include <NCollection_Sequence.hxx>
#include <LProp_SequenceOfCIType.hxx>
#include <LProp_CurAndInf.hxx>
#include <GeomAbs_CurveType.hxx>
#include <LProp_AnalyticCurInf.hxx>
#include <NCollection_Templates.hpp>

PYBIND11_MODULE(LProp, mod) {

	// IMPORT
	py::module::import("OCCT.Standard");
	py::module::import("OCCT.NCollection");
	py::module::import("OCCT.GeomAbs");

	py::module other_mod;

	// IMPORT GUARDS

	// ENUMS
	// C:\Miniconda\envs\occt\Library\include\opencascade\LProp_Status.hxx
	py::enum_<LProp_Status>(mod, "LProp_Status", "None")
		.value("LProp_Undecided", LProp_Status::LProp_Undecided)
		.value("LProp_Undefined", LProp_Status::LProp_Undefined)
		.value("LProp_Defined", LProp_Status::LProp_Defined)
		.value("LProp_Computed", LProp_Status::LProp_Computed)
		.export_values();
	// C:\Miniconda\envs\occt\Library\include\opencascade\LProp_CIType.hxx
	py::enum_<LProp_CIType>(mod, "LProp_CIType", "Identifies the type of a particular point on a curve: - LProp_Inflection: a point of inflection - LProp_MinCur: a minimum of curvature - LProp_MaxCur: a maximum of curvature.")
		.value("LProp_Inflection", LProp_CIType::LProp_Inflection)
		.value("LProp_MinCur", LProp_CIType::LProp_MinCur)
		.value("LProp_MaxCur", LProp_CIType::LProp_MaxCur)
		.export_values();

	// FUNCTIONS

	// CLASSES
	// C:\Miniconda\envs\occt\Library\include\opencascade\LProp_BadContinuity.hxx
	py::class_<LProp_BadContinuity, opencascade::handle<LProp_BadContinuity>, Standard_Failure> cls_LProp_BadContinuity(mod, "LProp_BadContinuity", "None");
	cls_LProp_BadContinuity.def(py::init<>());
	cls_LProp_BadContinuity.def(py::init<const Standard_CString>(), py::arg("theMessage"));
	cls_LProp_BadContinuity.def_static("Raise_", (void (*)(const Standard_CString)) &LProp_BadContinuity::Raise, "None", py::arg("theMessage"));
	cls_LProp_BadContinuity.def_static("Raise_", (void (*)(Standard_SStream &)) &LProp_BadContinuity::Raise, "None", py::arg("theMessage"));
	cls_LProp_BadContinuity.def_static("NewInstance_", (opencascade::handle<LProp_BadContinuity> (*)(const Standard_CString)) &LProp_BadContinuity::NewInstance, "None", py::arg("theMessage"));
	cls_LProp_BadContinuity.def_static("get_type_name_", (const char * (*)()) &LProp_BadContinuity::get_type_name, "None");
	cls_LProp_BadContinuity.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &LProp_BadContinuity::get_type_descriptor, "None");
	cls_LProp_BadContinuity.def("DynamicType", (const opencascade::handle<Standard_Type> & (LProp_BadContinuity::*)() const ) &LProp_BadContinuity::DynamicType, "None");

	// C:\Miniconda\envs\occt\Library\include\opencascade\LProp_NotDefined.hxx
	py::class_<LProp_NotDefined, opencascade::handle<LProp_NotDefined>, Standard_Failure> cls_LProp_NotDefined(mod, "LProp_NotDefined", "None");
	cls_LProp_NotDefined.def(py::init<>());
	cls_LProp_NotDefined.def(py::init<const Standard_CString>(), py::arg("theMessage"));
	cls_LProp_NotDefined.def_static("Raise_", (void (*)(const Standard_CString)) &LProp_NotDefined::Raise, "None", py::arg("theMessage"));
	cls_LProp_NotDefined.def_static("Raise_", (void (*)(Standard_SStream &)) &LProp_NotDefined::Raise, "None", py::arg("theMessage"));
	cls_LProp_NotDefined.def_static("NewInstance_", (opencascade::handle<LProp_NotDefined> (*)(const Standard_CString)) &LProp_NotDefined::NewInstance, "None", py::arg("theMessage"));
	cls_LProp_NotDefined.def_static("get_type_name_", (const char * (*)()) &LProp_NotDefined::get_type_name, "None");
	cls_LProp_NotDefined.def_static("get_type_descriptor_", (const opencascade::handle<Standard_Type> & (*)()) &LProp_NotDefined::get_type_descriptor, "None");
	cls_LProp_NotDefined.def("DynamicType", (const opencascade::handle<Standard_Type> & (LProp_NotDefined::*)() const ) &LProp_NotDefined::DynamicType, "None");

	// C:\Miniconda\envs\occt\Library\include\opencascade\LProp_CurAndInf.hxx
	py::class_<LProp_CurAndInf, std::unique_ptr<LProp_CurAndInf, Deleter<LProp_CurAndInf>>> cls_LProp_CurAndInf(mod, "LProp_CurAndInf", "Stores the parameters of a curve 2d or 3d corresponding to the curvature's extremas and the Inflection's Points.");
	cls_LProp_CurAndInf.def(py::init<>());
	cls_LProp_CurAndInf.def("AddInflection", (void (LProp_CurAndInf::*)(const Standard_Real)) &LProp_CurAndInf::AddInflection, "None", py::arg("Param"));
	cls_LProp_CurAndInf.def("AddExtCur", (void (LProp_CurAndInf::*)(const Standard_Real, const Standard_Boolean)) &LProp_CurAndInf::AddExtCur, "None", py::arg("Param"), py::arg("IsMin"));
	cls_LProp_CurAndInf.def("Clear", (void (LProp_CurAndInf::*)()) &LProp_CurAndInf::Clear, "None");
	cls_LProp_CurAndInf.def("IsEmpty", (Standard_Boolean (LProp_CurAndInf::*)() const ) &LProp_CurAndInf::IsEmpty, "None");
	cls_LProp_CurAndInf.def("NbPoints", (Standard_Integer (LProp_CurAndInf::*)() const ) &LProp_CurAndInf::NbPoints, "Returns the number of points. The Points are stored to increasing parameter.");
	cls_LProp_CurAndInf.def("Parameter", (Standard_Real (LProp_CurAndInf::*)(const Standard_Integer) const ) &LProp_CurAndInf::Parameter, "Returns the parameter of the Nth point. raises if N not in the range [1,NbPoints()]", py::arg("N"));
	cls_LProp_CurAndInf.def("Type", (LProp_CIType (LProp_CurAndInf::*)(const Standard_Integer) const ) &LProp_CurAndInf::Type, "Returns - MinCur if the Nth parameter corresponds to a minimum of the radius of curvature. - MaxCur if the Nth parameter corresponds to a maximum of the radius of curvature. - Inflection if the parameter corresponds to a point of inflection. raises if N not in the range [1,NbPoints()]", py::arg("N"));

	// C:\Miniconda\envs\occt\Library\include\opencascade\LProp_AnalyticCurInf.hxx
	py::class_<LProp_AnalyticCurInf, std::unique_ptr<LProp_AnalyticCurInf, Deleter<LProp_AnalyticCurInf>>> cls_LProp_AnalyticCurInf(mod, "LProp_AnalyticCurInf", "Computes the locals extremas of curvature of a gp curve Remark : a gp curve has not inflection.");
	cls_LProp_AnalyticCurInf.def(py::init<>());
	cls_LProp_AnalyticCurInf.def("Perform", (void (LProp_AnalyticCurInf::*)(const GeomAbs_CurveType, const Standard_Real, const Standard_Real, LProp_CurAndInf &)) &LProp_AnalyticCurInf::Perform, "None", py::arg("T"), py::arg("UFirst"), py::arg("ULast"), py::arg("Result"));

	// C:\Miniconda\envs\occt\Library\include\opencascade\LProp_SequenceOfCIType.hxx
	bind_NCollection_Sequence<LProp_CIType>(mod, "LProp_SequenceOfCIType");


}
