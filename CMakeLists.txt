set ( SOURCES
        "src/trajectory_line_creator.cpp"
        "src/trajectory_generator.cpp"
        "src/interface.cpp"
)

set (HEADERS
        "include/trajectory_line_creator.h"
        "include/trajectory_generator.h"
        "include/poly.h"
        "include/types.h"
        "src/trajectory.cpp"
        "include/trajectory.h"
        "src/BezierPolynomial.cpp"
        "include/BezierPolynomial.h"
        "src/BezierCurve.cpp"
        "include/BezierCurve.h"
)



include_directories("include")

add_library (trajectory_creator MODULE ${SOURCES} ${HEADERS})
target_link_libraries(trajectory_creator PRIVATE lmscore lms_math lms_sensor_utils street_environment phoenix_CC2016_service)
