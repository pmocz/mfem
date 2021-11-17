// Copyright (c) 2010-2021, Lawrence Livermore National Security, LLC. Produced
// at the Lawrence Livermore National Laboratory. All Rights reserved. See files
// LICENSE and NOTICE for details. LLNL-CODE-806117.
//
// This file is part of the MFEM library. For more information and source code
// availability visit https://mfem.org.
//
// MFEM is free software; you can redistribute it and/or modify it under the
// terms of the BSD-3 license. We welcome feedback and contributions, see file
// CONTRIBUTING.md for details.

#ifndef MFEM_LINEARFORM_EXT
#define MFEM_LINEARFORM_EXT

#include "../general/array.hpp"

namespace mfem
{

class LinearForm;
class FullLinearFormExtension;

/// Class extending the LinearForm class to support different AssemblyLevels.
class LinearFormExtension
{
protected:
   /// Linear form from which this extension depends. Not owned.
   LinearForm *lf;

public:
   LinearFormExtension(LinearForm *lf): lf(lf) { }

   virtual ~LinearFormExtension() { }

   /// Assemble at the level given for the LinearFormExtension subclass
   virtual void Assemble() = 0;
};

/// Data and methods for fully-assembled linear forms
class FullLinearFormExtension : public LinearFormExtension
{
private:
   /// Attributes of all mesh elements.
   Array<int> attributes;

   /// Temporary markers for device kernels.
   Array<int> markers;

public:
   FullLinearFormExtension(LinearForm *lf);

   /// Full assembly of the linear form, compatible with device execution.
   /// Only integrators added with AddDomainIntegrator are supported.
   void Assemble() override;
};

} // namespace mfem

#endif // MFEM_LINEARFORM_EXT
