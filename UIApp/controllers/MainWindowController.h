//  Copyright (c) 2007, Andrew Kimpton
//  
//  All rights reserved.
//  
//  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following
//  conditions are met:
//  
//  Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
//  Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer
//  in the documentation and/or other materials provided with the distribution.
//  The names of its contributors may not be used to endorse or promote products derived from this software without specific prior
//  written permission.
//  
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
//  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
//  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#import <Cocoa/Cocoa.h>

@class Z2ITSchedule;
@class ScheduleView;
@class RSWishlistController;
@class ProgramSearchViewController;

extern NSString *RSSSchedulePBoardType;

@interface MainWindowController : NSWindowController {
  IBOutlet NSSegmentedControl *mGetScheduleButton;
  IBOutlet NSSplitView *mScheduleSplitView;
  IBOutlet NSSplitView *mTopLevelSplitView;
  IBOutlet NSOutlineView *mViewSelectionOutlineView;
  IBOutlet NSView *mDetailView;
  IBOutlet NSView *mScheduleContainerView;
  IBOutlet ScheduleView *mScheduleView;
  IBOutlet NSPanel *mPredicatePanel;
  IBOutlet RSWishlistController *mWishlistController;
  IBOutlet NSObjectController *mCurrentSchedule;
  IBOutlet NSObjectController *mCurrentStation;
  IBOutlet NSObjectController *mCurrentLineup;
  IBOutlet NSTreeController *mViewSelectionTreeController;
  
  IBOutlet NSArrayController *mRecordingsArrayController;
  
  IBOutlet NSArrayController *mLineupsArrayController;
  
  IBOutlet ProgramSearchViewController *mProgramSearchViewController;
  
  float mDetailViewMinHeight;
  NSArray *mDraggedNodes;		// Temporary copy of the nodes being dragged around
}

- (IBAction) getScheduleAction:(id)sender;
- (IBAction) cleanupAction:(id)sender;
- (IBAction) recordShow:(id)sender;
- (IBAction) recordSeasonPass:(id)sender;
- (IBAction) watchStation:(id)sender;
- (IBAction) createWishlist:(id)sender;

- (void) setGetScheduleButtonEnabled:(BOOL)enabled;

- (void) setCurrentSchedule:(Z2ITSchedule*)inSchedule;
- (Z2ITSchedule*) currentSchedule;
@end