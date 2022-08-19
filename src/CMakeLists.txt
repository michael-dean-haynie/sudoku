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
        strategies/naked-single/naked-single.c
        strategies/no-duplicates/no-duplicates.c
)
target_include_directories(applibs PUBLIC
        .
        cell
        grid
        unit
        progress-event
        strategies/execute-strategies
        strategies/naked-single
        strategies/no-duplicates
        )

###################
# app target 
###################
add_executable(
        app
        app.c
)
target_link_libraries(app applibs)