/**************************************************************************/
/**
**  childDriver.cpp: This provides a test and example of the CHILD
**  interface.
**
**  The variation "childTestDriver" is used to test new additions,
**  especially to the childInterface.
**
**  Apr 2010
**
**  For information regarding this program, please contact Greg Tucker at:
**
**     Cooperative Institute for Research in Environmental Sciences (CIRES)
**     and Department of Geological Sciences
**     University of Colorado
**     2200 Colorado Avenue, Campus Box 399
**     Boulder, CO 80309-0399
**
*/
/**************************************************************************/

#include "childInterface.h"

int main( int argc, char **argv )
{
	childInterface myChildInterface;
	
	myChildInterface.Initialize( argc, argv );
	
	std::cout << "CHILD has finished initializing. Now for some tests.\n\n";
	
	std::cout << "Testing GetNodeCount(): this run has " 
	          << myChildInterface.GetNodeCount() << " nodes.\n";

	std::cout << "Testing GetNodeCoords() and GetValueSet() with 'elevation' and 'discharge':\n";
	std::cout << "The coordinates and properties of these nodes are:\n" 
	          << "(note that the two z columns should be the same)\n"
	          << "x\ty\tz\tz\tQ\tQs\n";
	int nn = myChildInterface.GetNodeCount();
	std::vector<double> coords = myChildInterface.GetNodeCoords();
	std::vector<double> elevs = myChildInterface.GetValueSet( "elevation" );
	std::vector<double> q = myChildInterface.GetValueSet( "discharge" );
	std::vector<double> qs = myChildInterface.GetValueSet( "sedflux" );
	for( long i=0; i<nn; i++ )
	{
	   std::cout << coords[3*i] << "\t" 
	             << coords[3*i+1] << "\t" << coords[3*i+2];
	   std::cout << "\t" << elevs[i]
	             << "\t" << q[i]
	             << "\t" << qs[i] << std::endl;
	}

	std::cout << "Testing GetTriangleCount(): this run has " 
	          << myChildInterface.GetTriangleCount() << " triangles.\n";

	std::cout << "Testing GetTriangleVertexIDs(): the vertex IDs of these triangles are:\n" 
	          << "Tri ID\tp0\tp1\tp2\n";
	int nt = myChildInterface.GetTriangleCount();
	std::vector<long> vertices = myChildInterface.GetTriangleVertexIDs();
	for( long i=0; i<nt; i++ )
	{
	   std::cout << i << "\t";
	   std::cout << vertices[3*i] << "\t";
	   std::cout << vertices[3*i+1] << "\t" 
	             << vertices[3*i+2] << std::endl;
	}


    // Now back to the main attraction ... running the model!
    
	if(1) // make this zero to use "example 2" below
	{
		// Example 1: using "Run" method, and setting run duration to zero so model reads duration from input file
		myChildInterface.Run( 0 );
	}
	else
	{
		// Example 2: using "RunOneStorm" 
		double mytime = 0;
		double myrunduration = 100000;
		
		while( mytime<myrunduration )
		{
			mytime = myChildInterface.RunOneStorm();
		}
	}
	
	std::cout << "CHILD run has finished. Now re-run the tests.\n\n";

	std::cout << "Testing GetNodeCount(): this run has " 
	          << myChildInterface.GetNodeCount() << " nodes.\n";

	std::cout << "Testing GetNodeCoords() and GetValueSet() with 'elevation' and 'discharge':\n";
	std::cout << "The coordinates and properties of these nodes are:\n" 
	          << "(note that the two z columns should be the same)\n"
	          << "x\ty\tz\tz\tQ\tQs\n";
	nn = myChildInterface.GetNodeCount();
	coords = myChildInterface.GetNodeCoords();
	elevs = myChildInterface.GetValueSet( "elevation" );
	q = myChildInterface.GetValueSet( "discharge" );
	qs = myChildInterface.GetValueSet( "sedflux" );
	for( long i=0; i<nn; i++ )
	{
	   std::cout << coords[3*i] << "\t" 
	             << coords[3*i+1] << "\t" << coords[3*i+2];
	   std::cout << "\t" << elevs[i]
	             << "\t" << q[i] << "\t" << qs[i] << std::endl;
	}

	std::cout << "Testing GetTriangleCount(): this run has " 
	          << myChildInterface.GetTriangleCount() << " triangles.\n";

	std::cout << "Testing GetTriangleVertexIDs(): the vertex IDs of these triangles are:\n" 
	          << "Tri ID\tp0\tp1\tp2\n";
	nt = myChildInterface.GetTriangleCount();
	vertices = myChildInterface.GetTriangleVertexIDs();
	for( long i=0; i<nt; i++ )
	{
	   std::cout << i << "\t";
	   std::cout << vertices[3*i] << "\t";
	   std::cout << vertices[3*i+1] << "\t" 
	             << vertices[3*i+2] << std::endl;
	}


	// Note that calling CleanUp() isn't strictly necessary, as the destructor will automatically clean it
	// up when myChildInterface is deleted ... but it's nice to be able to do this at will (and free up
	// memory)
	myChildInterface.CleanUp();
	
	return 0;
}
