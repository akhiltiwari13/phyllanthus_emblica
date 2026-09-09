# One target per question. The shared starting point lives in
# prep/templates/q00_template.cpp — copy it as qNN_<slug>.cpp for a new question.
add_executable(tt26_q01_packet_receiver q01_main.cpp q01_packet_receiver.cpp)
