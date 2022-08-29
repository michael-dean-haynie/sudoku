###################
# applibs target 
###################
add_library(
        applibs
        cell/cell.c
        grid/grid.c
        unit/unit.c
        progress-event/progress-event.c
        strategies/execute-strategies/execute-strategies.c
        strategies/no-duplicates/no-duplicates.c
        strategies/naked-pair/naked-pair.c
        strategies/naked-single/naked-single.c
        strategies/hidden-single/hidden-single.c
)
target_include_directories(applibs PUBLIC
        .
        cell
        grid
        unit
        progress-event
        strategies/execute-strategies
        strategies/no-duplicates
        strategies/naked-pair
        strategies/naked-single
        strategies/hidden-single
)

###################
# app target 
###################
add_executable(
        app
        app.c
)
target_link_libraries(app applibs)