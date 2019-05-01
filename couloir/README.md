# couloir


[![CircleCI](https://circleci.com/gh/yourgithubhandle/couloir/tree/master.svg?style=svg)](https://circleci.com/gh/yourgithubhandle/couloir/tree/master)


**Contains the following libraries and executables:**

```
couloir@0.0.0
│
├─test/
│   name:    TestCouloir.exe
│   main:    TestCouloir
│   require: couloir.lib
│
├─library/
│   library name: couloir.lib
│   namespace:    Couloir
│   require:
│
└─executable/
    name:    CouloirApp.exe
    main:    CouloirApp
    require: couloir.lib
```

## Developing:

```
npm install -g esy
git clone <this-repo>
esy install
esy build
```

## Running Binary:

After building the project, you can run the main binary that is produced.

```
esy x CouloirApp.exe 
```

## Running Tests:

```
# Runs the "test" command in `package.json`.
esy test
```
