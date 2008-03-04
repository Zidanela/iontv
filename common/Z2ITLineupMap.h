// libRecSchedCommon - Common code shared between UI application and background server
// Copyright (C) 2007 Andrew Kimpton
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

#import <CoreData/CoreData.h>

@class Z2ITStation;
@class Z2ITLineup;

@interface Z2ITLineupMap : NSManagedObject {

}

@property (retain) NSString * channel;
@property (retain) NSNumber * channelMinor;
@property (retain) NSDate * from;
@property (retain) NSDate * to;
@property (retain) Z2ITLineup * lineup;
@property (retain) Z2ITStation * station;

@end

// coalesce these into one @interface Z2ITLineupMap (CoreDataGeneratedAccessors) section
@interface Z2ITLineupMap (CoreDataGeneratedAccessors)
@end