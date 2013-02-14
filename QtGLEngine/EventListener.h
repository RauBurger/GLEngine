/*
 *  EventListener.h
 *  QtGLEngine
 *
 *  Created by Rob Rau on 12/20/10.
 *  Copyright 2010 Ypsilanti High School. All rights reserved.
 *
 */
#ifndef EVENTLISTENER_H_
#define EVENTLISTENER_H_


class EventListener
{
public:
	EventListener(){};
	~EventListener(){};
	
	virtual void FrameStart() = 0;
	virtual void FrameFinished() = 0;
private:
	
	
	
};

#endif //EVENTLISTENER_H_