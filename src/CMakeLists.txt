###################
# applibs target 
###################
add_library(
  applibs
  add.h
  add.c
  subtract.h
  subtract.c
)
target_include_directories(applibs PUBLIC . )

###################
# app target 
###################
add_executable(
  app
  app.c
)
target_link_libraries(app applibs)