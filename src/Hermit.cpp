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

#include <Standard_Handle.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Standard_TypeDef.hxx>
#include <Hermit.hxx>

PYBIND11_MODULE(Hermit, mod) {

	// IMPORT
	py::module::import("OCCT.Standard");
	py::module::import("OCCT.Geom2d");
	py::module::import("OCCT.Geom");

	py::module other_mod;

	// IMPORT GUARDS

	// ENUMS

	// FUNCTIONS

	// CLASSES
	// C:\Miniconda\envs\occt\Library\include\opencascade\Hermit.hxx
	py::class_<Hermit, std::unique_ptr<Hermit, Deleter<Hermit>>> cls_Hermit(mod, "Hermit", "This is used to reparameterize Rational BSpline Curves so that we can concatenate them later to build C1 Curves It builds and 1D-reparameterizing function starting from an Hermite interpolation and adding knots and modifying poles of the 1D BSpline obtained that way. The goal is to build a(u) so that if we consider a BSpline curve N(u) f(u) = ----- D(u)");
	cls_Hermit.def(py::init<>());
	cls_Hermit.def_static("Solution_", [](const opencascade::handle<Geom_BSplineCurve> & a0) -> opencascade::handle<Geom2d_BSplineCurve> { return Hermit::Solution(a0); }, py::arg("BS"));
	cls_Hermit.def_static("Solution_", [](const opencascade::handle<Geom_BSplineCurve> & a0, const Standard_Real a1) -> opencascade::handle<Geom2d_BSplineCurve> { return Hermit::Solution(a0, a1); }, py::arg("BS"), py::arg("TolPoles"));
	cls_Hermit.def_static("Solution_", (opencascade::handle<Geom2d_BSplineCurve> (*)(const opencascade::handle<Geom_BSplineCurve> &, const Standard_Real, const Standard_Real)) &Hermit::Solution, "returns the correct spline a(u) which will be multiplicated with BS later.", py::arg("BS"), py::arg("TolPoles"), py::arg("TolKnots"));
	cls_Hermit.def_static("Solution_", [](const opencascade::handle<Geom2d_BSplineCurve> & a0) -> opencascade::handle<Geom2d_BSplineCurve> { return Hermit::Solution(a0); }, py::arg("BS"));
	cls_Hermit.def_static("Solution_", [](const opencascade::handle<Geom2d_BSplineCurve> & a0, const Standard_Real a1) -> opencascade::handle<Geom2d_BSplineCurve> { return Hermit::Solution(a0, a1); }, py::arg("BS"), py::arg("TolPoles"));
	cls_Hermit.def_static("Solution_", (opencascade::handle<Geom2d_BSplineCurve> (*)(const opencascade::handle<Geom2d_BSplineCurve> &, const Standard_Real, const Standard_Real)) &Hermit::Solution, "returns the correct spline a(u) which will be multiplicated with BS later.", py::arg("BS"), py::arg("TolPoles"), py::arg("TolKnots"));
	cls_Hermit.def_static("Solutionbis_", [](const opencascade::handle<Geom_BSplineCurve> & BS, Standard_Real & Knotmin, Standard_Real & Knotmax, const Standard_Real TolPoles, const Standard_Real TolKnots){ Hermit::Solutionbis(BS, Knotmin, Knotmax, TolPoles, TolKnots); return std::tuple<Standard_Real &, Standard_Real &>(Knotmin, Knotmax); }, "returns the knots to insert to a(u) to stay with a constant sign and in the tolerances.", py::arg("BS"), py::arg("Knotmin"), py::arg("Knotmax"), py::arg("TolPoles"), py::arg("TolKnots"));


}
