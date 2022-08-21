build_example(
  NAME mao-test
  SOURCE_FILES mao-network-testbed.cc
  LIBRARIES_TO_LINK
    ${libcsma}
    ${libinternet}
    ${libinternet-apps}
    ${libpoint-to-point}
)
