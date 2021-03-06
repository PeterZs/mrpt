/* +---------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)               |
   |                          http://www.mrpt.org/                             |
   |                                                                           |
   | Copyright (c) 2005-2017, Individual contributors, see AUTHORS file        |
   | See: http://www.mrpt.org/Authors - All rights reserved.                   |
   | Released under BSD License. See details in http://www.mrpt.org/License    |
   +---------------------------------------------------------------------------+ */

#include <mrpt/poses/CPose3D.h>
#include <mrpt/poses/CPose3DInterpolator.h>
#include <mrpt/system/datetime.h>
#include <gtest/gtest.h>


TEST(CPose3DInterpolator,interp)
{
	using namespace mrpt::poses;
	using mrpt::math::TPose3D;
	using mrpt::utils::DEG2RAD;

	const mrpt::system::TTimeStamp t0 = mrpt::system::now();
	const mrpt::system::TTimeStamp dt = mrpt::system::secondsToTimestamp(0.10);

	CPose3DInterpolator pose_path;

	pose_path.insert( t0, TPose3D(1.,2.,3., DEG2RAD(30.0), DEG2RAD(.0),DEG2RAD(.0) ) );
	pose_path.insert( t0+2*dt, TPose3D(1.+3.,2.+4.,3.+5., DEG2RAD(30.0+20.0), DEG2RAD(.0),DEG2RAD(.0) ) );

	TPose3D interp;
	bool valid;
	pose_path.interpolate(t0+dt,interp,valid);

	EXPECT_TRUE(valid);
	const TPose3D interp_good(1.+1.5,2.+2.0,3.+2.5, DEG2RAD(30.0+10.0), DEG2RAD(.0),DEG2RAD(.0) );
	EXPECT_NEAR(.0, (CPose3D(interp_good).getHomogeneousMatrixVal() - CPose3D(interp).getHomogeneousMatrixVal()).array().abs().sum(), 1e-4);
}

