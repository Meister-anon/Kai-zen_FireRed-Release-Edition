#meant to read file and return filename and line at which string exceeds intended length of line
#think best to set hard set filename rather than try to automate
#ok think what I'll have to do is loop lines create loopid iterative variable to count the number of lines to be returned when I find an error
#set state toggle of found error to be reset on each new line well at start of main conditional code block
#since don't want to read the entire file I use a line within  the file as a ultimate break cut off point
#which I've already added to ability and moves files
#what I'll have to do is line search to find a description string start point ("
#use that as jumpoff point for main logic
#what I'll need from there is to loop the line itself or lenth of line?
#set start point at (" or "  store current iteration point of line as 0
#stop when I reach terminating point of line  \n  or just \ 
#do if statement here to do things without progressing
#set end point at that character subtract start point from end point if greater than line limit set found error to true
#reset start point to 0, from here start point won't be right since \n is 2 characters will have to subtract 1 from start point for rest of string
#continue loop rather than breaking stop again when I reach next \ character
#hmm actually dont reset start point to 0, that doesnt make sense end point si placement within enire line so shold just subtract from wher i start
#but just have 2 diff contidions first  if line character is " set start point to that
#after I hit end character \ after subtraction and at end of block reset starting point to current id + 2 that will get me to char after \n
#doesnt matter if there's nothing there if I hit eos before I reach another end point to subtract then it doesnt get used anyway
#if the ofudn error state is true I print file name and lineId
#since all I need is to identify where the issue is not how many there are per line
#I can have it break out at that point and continue to the next line

#since dex entry doesnt have everything on same line and different syntax I'd need slightly differnt code
#for just that file, but otherwise should be able to mostly copy paste once I get one file done
#just changing the line limit values

#dexLine_Limit 42
#movesLine_Limit 19
#abilityLine_Limit 41