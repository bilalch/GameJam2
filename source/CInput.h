#if !defined(_CINPUT_H_)
#define _CINPUT_H_

#include "IwGeom.h"
#include "s3ePointer.h"

#define MAX_TOUCHES		4

//
//
// CTouch - Represents a single touch
//
//
struct CTouch
{
public:
    int		x, y;		// Touch position
    bool	active;		// Touch active state
    int		id;			// ID of touch - The system tracks multiple touches by assigning each one a unique ID
};

//
//
// CInput - The CInput class is responsible for detecting multiple screen touches
//
//
class CInput
{
	// Properties
private:
	bool		Available;						// true if a pointer is present
	bool		IsMultiTouch;					// true if multitouch is enabled
	CTouch		Touches[MAX_TOUCHES];			// List of potential touches
public:
	bool		isAvailable() const { return Available; }			// Returns availability of the pointer
	bool		isMultiTouch() const { return IsMultiTouch; }		// Returns multitouch capability
	CTouch*		getTouchByID(int id);								// returns the touch identified by its id
	CTouch*		getTouch(int index) { return &Touches[index]; }		// Gets a specific touch
	CTouch*		findTouch(int id);									// Finds a specific touch by its id
	int			getTouchCount() const;								// Get number of touches this frame
	// Properties end

private:
public:
	bool		Init();							// Initialises the input system (returns true if pointer is supported)
	void		Release();						// Releases data used by the input system
	void		Update();						// Updates the input system, called every frame
};

extern CInput g_Input;



#endif	// _CINPUT_H_