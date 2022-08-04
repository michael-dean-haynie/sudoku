Overall goal is to deduce the value of each cell on the board.

So loop through each cell on the board

If the value has already been deduced (value is nonzero), then skip

else, if there is only 1 possible value - then assign it

else, start trying increasingly complex methods to reduce the possible values

    any time one of these methods makes progress, start over from the simplest methods and try them all again until no methods make progress
