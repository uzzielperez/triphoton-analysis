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
