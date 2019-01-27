# Integrator
A simple auto-FRS program using C++ Requests library ([cpr](https://whoshuu.github.io/cpr/)).

**Untested, use at your own risk!**

# How to use
1. Login to [integra](https://integra.its.ac.id/)
2. Copy your PHPSESSID (google on how to do this)
3. Git clone or download this repository
3. Navigate to `Release` folder
4. Edit `courses` and `config` file
5. Run `Integrator.exe`

# Courses
You can add courses simply by adding `course_code|class|curriculum_year|department_code` to your `courses` file, each course is separated by a new line. Use `_` if there is only one class available.

Example:
```
IF4101|A|2018|51100
KI1411|_|2014|51100
KI1440|C|2014|51100
```

# Config
Format:
```
NRP (10 digits)
PHPSESSID
Try count (optional, default: 5)
Try interval in seconds (optional, default: 5)
```

Example:
```
5117100086
vmil0meq2glraa29ffb3f6rh91
99
3
```
Using this config, the program will attempt to send courses POST request 99 times with 3 seconds delay in-between.

# Build Prerequisites
- [libcurl](https://curl.haxx.se/libcurl/)
- [cpr](https://whoshuu.github.io/cpr/)
