# makeClass

General instructions to start a makeClass:

```bash
mkdir EventLooper # Change to appropriate name
root -l
TChain chain("demo/fTree"); # or whatever the tree name is
chain.Add("../IDStudies/file.root")  # or whatever ntuple with a specific structure you have
chain.MakeClass("Triphoton") # or whatever name
```

*Latest and Greatest* Ntuple structure in EventLooper

### Make Histograms
To make histograms run:

```bash
root -l analyze.C

```

### To Add Histograms
Edit `AnalysesTools/makeClass/interface` and add histograms.
If this depends on a new Ntuple structure, please create update makeClass .h (WIP for script to do this automatically). See issue [here](https://github.com/uzzielperez/triphoton-analysis/issues/4).
