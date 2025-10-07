### compilation and running instructions

1. make build directory
`mkdir build`

2. in build directory run cmake
`cmake ..`

3. compile with make (needs sudo?)

4. run executable with:
    - ./sim <TARGET_DESIGN> (runs visualisation macro - only use this to visualise the geometry)
    - ./sim <TARGET_DESIGN> <macro_file.mac>
    - ./run.sh <TARGET_DESIGN> [identifier for filename (optional)]


- Is written using multithreading, so output files are written 1-per-thread, which then can be combined
(run.sh calls ./sim, then collects together info from temporary files into a single csv)

