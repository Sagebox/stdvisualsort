
#include "CSageBox.h"   // https://github.com/Sagebox
#include <algorithm>    

// -----------------------
// std::sort visualization
// -----------------------
//
// Shows 1024 unique pieces of data as it is being sorted by std::sort()
//
// While definitely using some fudging to meet the 10-line challenge, this shows how we can 
// use some of the Sagebox functions to peer inside of std::sort() and see how it is
// treating out data.
//
// This is a nice example of using some of the more advanced things C++ has to offer and
// a minimal set of Sagebox functions.
//
// ****** Press the Window close button when it finished to exit ******
//
// This is essentially the same code in the video, except for a few things:
//
//
// 1. A number of constexpr items were added.  This allows the number of items, interval (for making the display faster or slower), and the line height
//    easily changeable. 
//
// 2. A lookup of the last drawn linelength was added.  Since Windows GDI can be slow, and we're drawing an entire screen on each pass, the 
//    CheckValue() function only draw a line if it has changed.  This speeds up the process temendously. 
//    (realistically, putting all out to a memory bitmap and then drawing it would be the fastest approach)
//
// 3. srand() is used to seed the random number.  This leads to different outputs with different data -- still unique for each member, but ordered differently. 
//    it can show mroe how the sort() algorithim is working by looking at different data sets.  Changing srand to other numbers will change the sort input. 
//
// 4. I set the project to a debug mode.  This makes it a bit slower (because of all of the entry & exit stack and range checking on all the calls), as it 
//    was getting too fast to watch after I made the lookup (iLastValue array) modification
//
// note:  Some functions are combined (such as drawing in CheckValue()) becsause this source originally came from a 10-line challenge version.  If it written
//        without that in mind (i.e. more as normative code), some of the code below would be drawn out into more separated code with more specific and 
//        singular functions.
//
//        CheckValue(), for instance, needs to call PrintGraph() as separate function.  But, it's also an interesting use of the 
//        lambda callback for std::sort()
//
//        (I may come in and refactor this code to make it more in line with what I would write if I wasn't trying to keep it as short as possible for fun)
//

static int constexpr iNumItems      = 1400;
static int constexpr iLineHeight    = 512+15;
static int constexpr iInterval      = 1;

int main() 
{ 
    srand(123);
    auto &cWin = CSagebox::AutoWindow((1920-iNumItems)/2,150,iNumItems,43+iLineHeight,
        CString() << "10-Line std::sort() Visualization - " << iNumItems << " unique data elements.",opt::InnerSize()); 

    cWin.TextWidget(0,3+iLineHeight,"std::sort() Visualization",Font("Arial,28") | JustCenterX());

    int arr[iNumItems],iArray2[iNumItems]{};  // One for the values, one to help randomize with unique values

    // This algorithm for establishing a unique value is slow, but it works.  It's very inefficient.  It
    // was written this way to accomplish it in one line for the 10-line version. 

    for (int i=0;i<iNumItems;i++) while (iArray2[arr[i] = rand() % iNumItems]++); 

    int iLastLength[iNumItems]{};

    // Check the value and print the graph.  This was combined together due to the 10-line challenge code.
    // This should be separated to call PrintGraph() and then return a < b

    auto CheckValue = [&](int a,int b) 
    { 
        static int iCounter; 

        // Only print the graph in the Interval count. 
        // note: This number doesn't really apply like it used to.  When I added the iLastLength count, it sped up so much, 
        //       that even 0 or 1 is still pretty fast.  A way around it is to look at the last output time and 
        //       wait so many ms since the last output. 

        if (!(++iCounter % iInterval) || a < 0)
            for (int i=0;i<iNumItems;i++)
            {
                if (iLastLength[i] != arr[i])
                {
                    cWin.DrawLine({i,0}          ,{i,iLineHeight+1-arr[i]*iLineHeight/iNumItems},RgbColor().fromGray(i*24/iNumItems));   // A nice cloudy gradient
                    cWin.DrawLine({i,iLineHeight},{i,iLineHeight-arr[i]*iLineHeight/iNumItems},CTools::HSLtoRGB({(double) arr[i]/iNumItems,1,.5})); 
                    iLastLength[i] = arr[i];
                }
            }
        
        cWin.Update();  // We don't need this since auto-updates are on.  This update is forced to slow the display down on purpose. 
                        // Otherwise, the auto update (which updates every 10-20ms) works well and causes this to run much too fast
                        // The other alternsative is to slow it down on a timer. 
                        //
                        // note: This only updates if we've put anything out to the window since it last updated. 
                        //       So, even though this is free-floating, no update will occur unless we printed the graph above.

        return a < b;   // return the comparison for sort()
    };

    std::sort(&arr[0],&arr[iNumItems],[&](int a,int b) { return CheckValue(a,b); });

    CheckValue(-1,0);           // Force an update so we get the current graph (This should turn into PrintGraph()
    return cWin.WaitforClose(); // Wait for the user to close the window. 
} 
