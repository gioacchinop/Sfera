//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Apr 14 17:23:36 2019 by ROOT version 6.14/04
// from TTree tree/
// found on file: Run_2_Data_4_11_2019_Ascii.root
//////////////////////////////////////////////////////////

#ifndef DataTree_h
#define DataTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class DataTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           ev;
   Int_t           nch;
   Float_t         base[16];   //[nch]
   Float_t         vamp[16];   //[nch]
   Float_t         vcharge[16];   //[nch]
   Float_t         letime[16];   //[nch]
   Float_t         tetime[16];   //[nch]
   Float_t         ratecount[16];   //[nch]
   Float_t         pshape[16][1024];   //[nch]

   // List of branches
   TBranch        *b_ev;   //!
   TBranch        *b_nch;   //!
   TBranch        *b_base;   //!
   TBranch        *b_vamp;   //!
   TBranch        *b_vcharge;   //!
   TBranch        *b_letime;   //!
   TBranch        *b_tetime;   //!
   TBranch        *b_ratecount;   //!
   TBranch        *b_pshape;   //!

   DataTree(TTree *tree=0);
   virtual ~DataTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef DataTree_cxx
#include<iostream>
DataTree::DataTree(TTree *tree) : fChain(0)
{
    // if parameter tree is not specified (or zero) exit
    if (tree == 0) {
        std::cout << "No tree has been provided. exiting!" << std::endl;
        exit(-1)
    }
    Init(tree);
}

DataTree::~DataTree()
{
   if (!fChain) return;
   //delete fChain->GetCurrentFile();
}

Int_t DataTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t DataTree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void DataTree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("ev", &ev, &b_ev);
   fChain->SetBranchAddress("nch", &nch, &b_nch);
   fChain->SetBranchAddress("base", base, &b_base);
   fChain->SetBranchAddress("vamp", vamp, &b_vamp);
   fChain->SetBranchAddress("vcharge", vcharge, &b_vcharge);
   fChain->SetBranchAddress("letime", letime, &b_letime);
   fChain->SetBranchAddress("tetime", tetime, &b_tetime);
   fChain->SetBranchAddress("ratecount", ratecount, &b_ratecount);
   fChain->SetBranchAddress("pshape", pshape, &b_pshape);
   Notify();
}

Bool_t DataTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void DataTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t DataTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef DataTree_cxx
