I want to create UI that can play forwards and backwards through the solving of a puzzle.

I want the UI to be web-based so it is maximally portable.

I want the UI to be able to go forwards and backwards.

I want the UI to allow automatically playing with configurable speed.

I want the UI to be able to move forward step by step manually.

I want to be able to disable logging for performance

I want the playback to be configurably granular in how much detail is played back.
For example, it may just play back the progress events, or it may play back all accessed and such

I want the UI to be able to show the following things

- the sudoku board and it's current state
  - rows and columns labeled
  - which cell the program is currently trying to make progress on
  - the strategy by which the program is currently trying to make progress
  - the units involved in making progress
  - the cells involved in making progress
  - which cell(s) were just progressed

- in progress statistics like
  - how solved the board is %-wise
  - how many times a strategy has been used (over all cells)
  - cell-specific stuff
    - how many times this cell has been "accessed" as part of other strategies
      - how many times the value has been checked
      - how many times the notes have been checked
    - the history of access on this cell
  - the history of progress made on this cell


Example with naked single
  - highlight the cell that starting the current analysis with
  - check if the cell is already solved // false
  - count how many notes the cell has // 1
  - apply naked single strategy
  - update cell with results of proof
  - log state change/progress event

Example with hidden single
- highlight the cell that we're starting the current analysis with
- check if the cell is already solved // false
- count how many notes the cell has // [2-9]
- apply hidden single strategy
  - highlight/log the unit we're about to analyze // for example the row
  - highlight/log each cell in the unit as we analyze them
  - somehow keep reference of these, so we can know/highlight which cells were part of the proof we're building
- log state change / progress event / proof
  - include the unit as part of the proof
  - include each cell in unit that was analyzed as part of the proof

Types of logs/records
- (ProofBasisTarget)Log that says "Hey we're going to start with this cell and see if we can solve it or make progress on any of its sibling cells in the units that it is a part of"
  - can be referenced as context
- Log that says "hey I inspected this cell's value as part of [some context]"
- Log that says "hey I inspected this cell's notes as part of [some context]"
- Log that says "hey I inspected this cell's coordinates as part of [some context]"
- Log that says "hey we're gonna try this strategy as part of [some context]"
- Log that says "hey we're focusing on these units as part of [some context]"
- 
