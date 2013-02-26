#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "transit.h"
#include "tree.h"

vector<string> &split(const string &s, char delim, vector<string> &elems) {
  stringstream ss(s);
  string item;
  while(getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}
vector<string> split(const string &s, char delim) {
  vector<string> elems;
  return split(s, delim, elems);
}
/*********************************************************/
int main(int argc, char** argv){
/*parsing the command line*/
  char *outfile = NULL;
  int index,verbose_flag,c,outflag=0,harm_flag=1,orig_flag=1;
  int colp, coldsp,pmax=5,ap=0,np;
  string ID;
  string ext=".blsanal";
  opterr = 0;
//  while ((c = getopt (argc, argv, "i:o:")) != -1)
  while(1){
    static struct option long_options[] =
    {
      /* These options set a flag. */
      {"verbose", no_argument,       &verbose_flag, 1},
      {"brief",   no_argument,       &verbose_flag, 0},
      {"noharm",   no_argument,       &harm_flag, 0},
      {"noorigin",   no_argument,       &orig_flag, 0},
      {"help", no_argument, 0, 'h'},
      /* These options don't set a flag.
       * We distinguish them by their indices. */
      {"infile",  required_argument, 0, 'i'},
      {"outfile", required_argument, 0, 'o'},
      {"colp",    required_argument, 0, 'p'},
      {"coldsp",    required_argument, 0, 'd'},
      {"ap",    required_argument, 0, 'a'},
      {"pmax",    required_argument, 0, 'm'},
      {"ext",    required_argument, 0, 'e'},
      {0, 0, 0, 0}
    };
    /* getopt_long stores the option index here. */
    int option_index = 0;
    c = getopt_long (argc, argv, "hi:o:p:d:a:m:e:", long_options, &option_index);
    /* Detect the end of the options. */
    if (c == -1)
      break;
    switch (c)
    {
      case 0:
      /* If this option set a flag, do nothing else now. */
        if (long_options[option_index].flag != 0)
          break;
        printf ("option %s", long_options[option_index].name);
        if (optarg)
          printf (" with arg %s", optarg);                                    
        printf ("\n");
        break;
      case 'h':
        printf("Options are hi:o:p:d:a:m:e:\n");
        printf("Usage: \n");
        printf("-h --help print out help information\n");
        printf("-i --infile [string] the base id [required argument]\n");
        printf("-o --outfile [string] the outfile name, if not set, output to screen\n");
        printf("-p --colp [int] the colomn number for period\n");
        printf("-d --coldsp [int] the colomn number for dsp\n");
        printf("-a --ap [int] the aperture number to run the program\n");
        printf("-m --pmax [int] the maximum number of peaks(reconstructed files)to merge \n");
        printf("-e --ext [string] the externtion of file\n");
        printf("--noharm ignore the harmonic peaks\n");
        printf("--noorigin do not record the orgin of the peaks\n");
        return 0;
        break;
      case 'i':
        ID = optarg;
        break;
      case 'o':
        outfile = optarg;
        break;
      case 'p':
        colp = atoi(optarg);
        break;
      case 'd':
        coldsp = atoi(optarg);
        break;
      case 'a':
        ap = atoi(optarg);
        break;
      case 'm':
        pmax = atoi(optarg);
        break;
      case 'e':
        ext = optarg;
        break;
      case '?':
        if (optopt == 'i')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        if (optopt == 'o')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        if (optopt == 'p')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        if (optopt == 'd')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        if (optopt == 'a')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        if (optopt == 'm')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        if (optopt == 'e')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,"Unknown option character `\\x%x'.\n",optopt);
        return 1;
      default:
        abort();
    }
  }
  // cout<<ID<<outfile<<ap<<pmax<<ext<<endl;
  //printf ("aflag = %d, bflag = %d, cvalue = %s\n",aflag, bflag, cvalue);
    for (index = optind; index < argc; index++){
      printf ("Non-option argument %s\n", argv[index]);
      return 1;
    }
    if(ID.empty()){
      cout << "--infile [-i] is required for sorttransit\n";
      return 1;
    }
    ifstream in;
    ofstream out;
    if (!(outfile==NULL)) outflag=1;
    double p,dsp;
    double *parr = new double [pmax];
    string infile,line;
    Item *item;
    Tree *root = new Tree();
    vector <string> data;
    //cout << harm_flag << endl;
    if(!orig_flag){
      delete [] parr;
    } else {
      ifstream oin;
      string oinfile;
      sprintf(&oinfile[0],"%s%s",ID.c_str(),ext.c_str());
      oin.open(&oinfile[0]);
      np=0;
      while(!oin.eof() and np<pmax){      
        getline(oin,line);
        if(line.compare(0,1,"#") and !line.empty()){
         data = split(line,'\t'); 
         parr[np] = atof(data[colp].c_str());
         np++;
        }
      }
      oin.close();
    }
    for (np=0;np<pmax;np++){
      sprintf(&infile[0],"%s.AP%d.P%d%s",ID.c_str(),ap,np,ext.c_str());
      //cout << &infile[0] << np << endl;
      //infile << ID << ".AP" << ap << ".P" << np << ".blsanal"; 
      //in.open("HAT-317-0002127.AP0.P0.blsanal");
      //in.open("HAT-317-0002127.AP0.P0.blsanal");
      in.open(&infile[0]);
      if(!in){
       exit(1);
      }
      while(!in.eof()){
        getline(in,line);
        if(line.compare(0,1,"#") and !line.empty()){
         data = split(line,'\t'); 
         p = atof(data[colp].c_str());
         dsp = atof(data[coldsp].c_str());
         if(orig_flag){
           string pstr;
           sprintf(&pstr[0],"%5d%15.7f",np,parr[np]);
           line.append(&pstr[0]);
           //cout << &pstr[0] << endl;
           //cout << line << endl;
         }
         Item *newitem = new Item(&line,p,dsp,harm_flag);
         Tree *node = new Tree(newitem);
         root->Insert(*node);
         delete node;
      //   printf("nb of nodes %d\n",nb);
       }
        if(!in) break;
      }
      in.close();
    }
    if(orig_flag){
      delete [] parr;
    }
    if(outflag){
      vector <string> outstr(1,"#merged files"); 
      root->InorderPrint(outstr); 
      //cout << outstr.size() << endl;
      out.open(outfile);
      for (unsigned int i=0; i<outstr.size();i++){
        out<<outstr[i]<<"\n";
      }
      out.close();
    } else {
      vector <string> outstr = vector<string> (); 
      root->InorderPrint(outstr); 
    }
    delete root;
}
