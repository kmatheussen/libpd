/*-----------------------------------------------------------------
LOG
    GEM - Graphics Environment for Multimedia

    translate a gem object

    Copyright (c) 1997-1999 Mark Danks. mark@danks.org
    Copyright (c) Günther Geiger. geiger@epy.co.at
    Copyright (c) 2001-2011 IOhannes m zmölnig. forum::für::umläute. IEM. zmoelnig@iem.at
    For information on usage and redistribution, and for a DISCLAIMER OF ALL
    WARRANTIES, see the file, "GEM.LICENSE.TERMS" in this distribution.

-----------------------------------------------------------------*/

#ifndef _INCLUDE__GEM_MANIPS_TRANSLATEXYZ_H_
#define _INCLUDE__GEM_MANIPS_TRANSLATEXYZ_H_

#include "Base/GemBase.h"

/*-----------------------------------------------------------------
-------------------------------------------------------------------
CLASS
    translateXYZ
    
    translate a gem object

DESCRIPTION
    
    Inlet for X - "xVal"
    Inlet for Y - "yVal"
    Inlet for Z - "zVal"

-----------------------------------------------------------------*/
class GEM_EXTERN translateXYZ : public GemBase
{
    CPPEXTERN_HEADER(translateXYZ, GemBase);

    public:

        //////////
        // Constructor
    	translateXYZ(int argc, t_atom *argv);
    	
    protected:
    	
    	//////////
    	// Destructor
    	virtual ~translateXYZ();

    	//////////
    	// When rendering occurs
    	virtual void	render(GemState *state);

    	//////////
    	// The translation vector (x, y, z)
    	float	    	m_vector[3];

    	//////////
    	// X value changed
    	void	    	xMess(float val);
    	
    	//////////
    	// Y value changed
    	void	    	yMess(float val);
    	
    	//////////
    	// Z value changed
    	void	    	zMess(float val);
    	
    private:
    	
    	//////////
    	// static member functions
    	static void 	xMessCallback(void *data, t_floatarg val);
    	static void 	yMessCallback(void *data, t_floatarg val);
    	static void 	zMessCallback(void *data, t_floatarg val);
};

#endif	// for header file
