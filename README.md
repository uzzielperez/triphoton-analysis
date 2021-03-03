# Analysis Code Base Structure

```
├── Analyzers                # From MiniAOD/AOD to Ntuples
├── AnalysesTools            # From Ntuples to Histograms to Pretty Plots
    ├── makeClass
    ├── makePrettyPlots
├── LICENSE
└── README.md
```


## Making Pretty Plots

```
.
    ├── ...
    ├── makePrettyPlots
    │   ├── README.md    # usage
    │   ├── bin          # executables
    │   ├── interface    # reusable stuff
    │   ├── data
    │   ├── test          # Unit tests
    │   ├── scripts       # miscellaneous scripts
    │   └── python        # python plotters or scripts
    └── ...
.
```
