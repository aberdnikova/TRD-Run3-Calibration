#ifndef ALI_AS_ANALYSIS_TRD_DIGITS_H
#define ALI_AS_ANALYSIS_TRD_DIGITS_H

class AliTRDdigitsManager;

#include "AliAnalysisTaskSE.h"

#include "TMath.h"
#include "TObject.h"
#include "TClonesArray.h"
#include "TLorentzVector.h"
//#include "Ali_AS_Event.h"



//----------------------------------------------------------------------------------------
class Ali_AS_TRD_digit : public TObject
{
private:
    // Digit data
    UShort_t hit_ids[2]; // contains the full information of the TRD hit position (sector, stack, layer, row, column), definition see below
    Short_t ADC_time_values[24]; // raw ADC values for all 24 time bins of a single pad
    Short_t arr_pos[3][24];
    //Short_t arr_pos_uncalib[3][24]
    //Short_t ADC_time_values_corrected_tc[24]; // raw ADC values for all 24 time bins of a single pad
    Short_t  dca_to_track; // distance of closest approach of digit TRD hit to TPC track
    Short_t  dca_x;
    Short_t  dca_y;
    Short_t  dca_z;
    Short_t  ImpactAngle; // impact angle of TPC track to this TRD digit

public:
    Ali_AS_TRD_digit() :
	//hit_ids(), ADC_time_values(), ADC_time_values_corrected(), ADC_time_values_corrected_tc(), dca_to_track(-1), dca_x(-1), dca_y(-1), dca_z(-1), ImpactAngle(-1)
        hit_ids(), ADC_time_values(), arr_pos(), /*arr_pos_uncalib(),*/dca_to_track(-1), dca_x(-1), dca_y(-1), dca_z(-1), ImpactAngle(-1)
    {
    }
	~Ali_AS_TRD_digit() {}

	// setters
	void sethit_ids(UShort_t x, UShort_t y)                     { hit_ids[0] = x; hit_ids[1] = y; }
	void setADC_time_value(Int_t time_bin, Short_t ADC_value)  { ADC_time_values[time_bin] = ADC_value; }
        void set_pos(Int_t time_bin, Float_t x_pos, Float_t y_pos, Float_t z_pos) //{arr_pos[0][time_bin] = (Short_t)(100.0*x_pos); arr_pos[1][time_bin] = (Short_t)(100.0*y_pos); arr_pos[2][time_bin] = (Short_t)(100.0*z_pos);}

        {
            TVector3 vec_200cm(x_pos,y_pos,z_pos);
            vec_200cm *= 200.0/vec_200cm.Mag();

            arr_pos[0][time_bin] = (Short_t)(100.0*(x_pos-vec_200cm.X())); arr_pos[1][time_bin] = (Short_t)(100.0*(y_pos-vec_200cm.Y())); arr_pos[2][time_bin] = (Short_t)(100.0*(z_pos-vec_200cm.Z()));

            //cout << "x_pos: " << x_pos << endl;
            //cout << "y_pos: " << y_pos << endl;
            //cout << "z_pos: " << z_pos << endl;
            //cout << "x_pos-200: " << arr_pos[0][time_bin] << endl;
            //cout << "y_pos-200: " << arr_pos[1][time_bin] << endl;
            //cout << "z_pos-200: " << arr_pos[2][time_bin] << endl;
        }

        //void set_pos_uncalib(Int_t time_bin, Float_t x_pos_uncalib, Float_t y_pos_uncalib, Float_t z_pos_uncalib)  { arr_pos_uncalib[0][time_bin] = (Short_t)(100.0*x_pos_uncalib); arr_pos[1][time_bin] = (Short_t)(100.0*y_pos); arr_pos_uncalib[2][time_bin] = (Short_t)(100.0*z_pos_uncalib); }


        //void setADC_time_value_corrected_tc(Int_t time_bin, Short_t ADC_value)  { ADC_time_values_corrected_tc[time_bin] = ADC_value; }
        void setdca_to_track(Float_t f, Float_t f_x, Float_t f_y, Float_t f_z) { dca_to_track = (Short_t)(100.0*f); dca_x = (Short_t)(100.0*f_x); dca_y = (Short_t)(100.0*f_y); dca_z = (Short_t)(100.0*f_z);}
	void setImpactAngle(Float_t f)                              { ImpactAngle = (Short_t)(100.0*f); }

        // TVector3 vec_blubb(x_pos,y_pos,z_pos);
        // vec_blubb *= 1.0/vec_blubb.Mag(); // normalize the vector to length 1

        // vector = {260.0,100,0}
        // norm_vector = vector/length_of_vector;
        // norm_vector *= 200.0;
        // vector = {260.0,100,0} - norm_vector;

	// getters
        UInt_t   gethit_ids(Int_t i)                const           { return hit_ids[i]; }
	Short_t  getADC_time_value(Int_t time_bin)  const           { return ADC_time_values[time_bin]; }
        Float_t  get_pos(Int_t time_bin, Int_t index)  const //{ return ((Float_t)arr_pos[index][time_bin])/100.0; }
        {
            TVector3 vec_200cm((Float_t)arr_pos[0][time_bin]/100.0,(Float_t)arr_pos[1][time_bin]/100.0,(Float_t)arr_pos[2][time_bin]/100.0);
            
            //now vec_200cm is again in cm

            //vec_200cm *= 200.0/vec_200cm.Mag();     //when we get positions XYZ-200cm
            vec_200cm *= 1.0/vec_200cm.Mag();         //for the moment
            return (Float_t)(arr_pos[index][time_bin]/100.0 + vec_200cm(index));
        }

        //Float_t  get_pos_uncalib(Int_t time_bin, Int_t index)  const { return ((Float_t)arr_pos_uncalib[index][time_bin])/100.0; }
        //Short_t  getADC_time_value_corrected_tc(Int_t time_bin)  const { return ADC_time_values_corrected_tc[time_bin]; }
	Float_t  getdca_to_track()                  const           { return ((Float_t)dca_to_track)/100.0; }
	Float_t  getdca_x()                         const           { return ((Float_t)dca_x)/100.0; }
	Float_t  getdca_y()                         const           { return ((Float_t)dca_y)/100.0; }
        Float_t  getdca_z()                         const           { return ((Float_t)dca_z)/100.0; }
	Float_t  getImpactAngle()                   const           { return ((Float_t)ImpactAngle)/100.0; }

	// x = TRD_col + TRD_sec*144;
        // y = TRD_row + TRD_stack*16 + TRD_lay*16*5;
	Int_t    get_sector()                       const           { return (Int_t)((Float_t)hit_ids[0]/144.0); }
	Int_t    get_column()                       const           { return (hit_ids[0]%144); }
	Int_t    get_layer()                        const           { return (Int_t)((Float_t)hit_ids[1]/(16.0*5.0)); }
	Int_t    get_stack()                        const           { return ((Int_t)((Float_t)hit_ids[1]/16.0))%5; }
	Int_t    get_row()                          const           { return (hit_ids[1]%16); }

        Int_t    get_detector(Int_t layer, Int_t stack, Int_t sector) const { return (layer + stack * 6 + sector * 6 * 5);}

	ClassDef(Ali_AS_TRD_digit,1);  //
};


class Ali_AS_Track : public TObject
{
private:
    // Track properties
    Float_t        nsigma_e_TPC; // nsigma dE/dx of particle
    Float_t        nsigma_e_TOF; // nsigma TOF of particle
    Float_t        nsigma_pi_TPC; // nsigma dE/dx of particle
    Float_t        nsigma_pi_TOF; // nsigma TOF of particle
    Float_t        nsigma_K_TPC; // nsigma dE/dx of particle
    Float_t        nsigma_K_TOF; // nsigma TOF of particle
    Float_t        nsigma_p_TPC; // nsigma dE/dx of particle
    Float_t        nsigma_p_TOF; // nsigma TOF of particle
    Float_t        TRD_signal; // TRD PID signal
    Float_t        TRDsumADC; // TRD electron PID probability
    Float_t        dca; // distance of closest approach of particle A
    TLorentzVector TLV_part; // Lorentz vector properties of this particle
    UShort_t       NTPCcls; // Number of TPC clusters
    UShort_t       NTRDcls; // Number of TRD clusters
    UShort_t       NITScls; // Number of TRD clusters
    UShort_t       status; // status of track: bit 0: ITS refit, bit1: TPC refit
    Float_t        TPCchi2; // TPC chi2
    ULong64_t      TRD_ADC_time_layer[6];
    Float_t        impact_angle_on_TRD; // Track impact angle on TRD
    Float_t        TPCdEdx; // Energy loss information of TPC
    Float_t        TOFsignal; // Time-of-flight
    Float_t        Track_length; // length of track
    Float_t        aliHelix_params[9];

    UShort_t      fNumTRDdigits; // number of TRD digits for this track

    TClonesArray* fTRD_digits;      //->

public:
    Ali_AS_Track() :
	nsigma_e_TPC(-1),nsigma_e_TOF(-1),nsigma_pi_TPC(-1),nsigma_pi_TOF(-1),nsigma_K_TPC(-1),nsigma_K_TOF(-1),nsigma_p_TPC(-1),nsigma_p_TOF(-1),TRD_signal(-1),
        TRDsumADC(-1),dca(-1),TLV_part(),NTPCcls(-1),NTRDcls(-1),NITScls(-1),status(-1),TPCchi2(-1),TRD_ADC_time_layer(),
        impact_angle_on_TRD(-1),TPCdEdx(-1),TOFsignal(-1),Track_length(-1),aliHelix_params(),fNumTRDdigits(0)
    {
	fTRD_digits      = new TClonesArray( "Ali_AS_TRD_digit", 10 );
    }
	~Ali_AS_Track()
	{
	    delete fTRD_digits;
	    fTRD_digits = NULL;
	}

	// setters
	void setnsigma_e_TPC(Float_t f)                     { nsigma_e_TPC = f;         }
	void setnsigma_e_TOF(Float_t f)                     { nsigma_e_TOF = f;         }
	void setnsigma_pi_TPC(Float_t f)                     { nsigma_pi_TPC = f;         }
	void setnsigma_pi_TOF(Float_t f)                     { nsigma_pi_TOF = f;         }
	void setnsigma_K_TPC(Float_t f)                     { nsigma_K_TPC = f;         }
	void setnsigma_K_TOF(Float_t f)                     { nsigma_K_TOF = f;         }
	void setnsigma_p_TPC(Float_t f)                     { nsigma_p_TPC = f;         }
	void setnsigma_p_TOF(Float_t f)                     { nsigma_p_TOF = f;         }
	void setTRDSignal(Float_t f)                     { TRD_signal = f;         }
	void setTRDsumADC(Float_t f)                     { TRDsumADC = f;         }
	void setdca(Float_t f)                    { dca = f;        }
	void set_TLV_part(TLorentzVector tlv)     { TLV_part = tlv; }
	void setNTPCcls(UShort_t s)               { NTPCcls = s;}
	void setNTRDcls(UShort_t s)               { NTRDcls = s;}
	void setNITScls(UShort_t s)               { NITScls = s;}
	void setStatus(UShort_t s)                { status = s;}
	void setTPCchi2(Float_t f)                { TPCchi2 = f;}
        void setTRD_layer(Int_t i_layer, ULong64_t l)  { TRD_ADC_time_layer[i_layer] = l;}
        void setimpact_angle_on_TRD(Float_t f)           {impact_angle_on_TRD = f;}
	void setTPCdEdx(Float_t f)                       {TPCdEdx = f;}
	void setTOFsignal(Float_t f)                     {TOFsignal = f;}
        void setTrack_length(Float_t f)                  {Track_length = f;}
        void setHelix(Float_t a, Float_t b,Float_t c,Float_t d,Float_t e,Float_t f,Float_t g,Float_t h,Float_t i)
        {
            aliHelix_params[0] = a;
            aliHelix_params[1] = b;
            aliHelix_params[2] = c;
            aliHelix_params[3] = d;
            aliHelix_params[4] = e;
            aliHelix_params[5] = f;
            aliHelix_params[6] = g;
            aliHelix_params[7] = h;
            aliHelix_params[8] = i;
        }

	// getters
	Float_t getnsigma_e_TPC() const                     { return nsigma_e_TPC;         }
	Float_t getnsigma_e_TOF() const                     { return nsigma_e_TOF;         }
	Float_t getnsigma_pi_TPC() const                     { return nsigma_pi_TPC;         }
	Float_t getnsigma_pi_TOF() const                     { return nsigma_pi_TOF;         }
	Float_t getnsigma_K_TPC() const                     { return nsigma_K_TPC;         }
	Float_t getnsigma_K_TOF() const                     { return nsigma_K_TOF;         }
	Float_t getnsigma_p_TPC() const                     { return nsigma_p_TPC;         }
	Float_t getnsigma_p_TOF() const                     { return nsigma_p_TOF;         }
	Float_t getTRDSignal() const                     { return TRD_signal;         }
	Float_t getTRDsumADC() const                     { return TRDsumADC;         }
	Float_t getdca() const                    { return dca;        }
	TLorentzVector get_TLV_part() const       { return TLV_part;   }
	UShort_t getNTPCcls() const               { return NTPCcls;    }
	UShort_t getNTRDcls() const               { return NTRDcls;    }
	UShort_t getNITScls() const               { return NITScls;    }
	UShort_t getStatus() const               { return status;    }
	Float_t  getTPCchi2() const              { return TPCchi2; }
        ULong64_t getTRD_layer(Int_t i_layer) const   { return TRD_ADC_time_layer[i_layer]; }
        Float_t   getimpact_angle_on_TRD() const    { return impact_angle_on_TRD; }
	Float_t   getTPCdEdx() const                { return TPCdEdx; }
	Float_t   getTOFsignal() const              { return TOFsignal; }
        Float_t   getTrack_length() const           { return Track_length; }
        Float_t   getHelix_param(Int_t i_param) const              {return aliHelix_params[i_param]; }


	Float_t   getTRD_ADC(Int_t i_layer, Int_t i_time_bin) const
	{
	    if(i_layer < 0 || i_layer > 5 || i_time_bin < 0 || i_time_bin > 7) return -1; // out of range
	    ULong64_t TRD_value = 0;
	    for(Int_t i_bit = 0; i_bit < 8; i_bit++) // One single time slice 8 bit = 256
	    {
		Int_t bitcheck = i_bit + 8*i_time_bin; // range: 0..63 = 64 bit = 8 byte = Long64_t
		Int_t bit_status = (TRD_ADC_time_layer[i_layer] >> bitcheck) & 1; // check bit bitcheck
		if(bit_status) TRD_value |= (ULong64_t)1 << i_bit; // setting bit i_bit to 1
	    }
	    Float_t TRD_value_decode = (Float_t)TRD_value * 100.0; // * TRD_ADC_bin_width
	    return TRD_value_decode;
	}

	Int_t     HasITShit_on_layer(Int_t ilayer) { return ((NITScls >> ilayer) & 1);}  // ITShit -> LOL


	Ali_AS_TRD_digit* createTRD_digit()
	{
	    if (fNumTRDdigits == fTRD_digits->GetSize())
		fTRD_digits->Expand( fNumTRDdigits + 10 );
	    if (fNumTRDdigits >= 10000)
	    {
		Fatal( "Ali_AS_Track::createTRD_digit()", "ERROR: Too many TRD digits (>10000)!" );
		exit( 2 );
	    }

	    new((*fTRD_digits)[fNumTRDdigits++]) Ali_AS_TRD_digit;
	    return (Ali_AS_TRD_digit*)((*fTRD_digits)[fNumTRDdigits - 1]);
	}
	void clearTRD_digit_list()
	{
	    fNumTRDdigits   = 0;
	    fTRD_digits      ->Clear();
	}
	UShort_t getNumTRD_digits() const
	{
	    return fNumTRDdigits;
	}
	Ali_AS_TRD_digit* getTRD_digit(UShort_t i) const
	{
	    return i < fNumTRDdigits ? (Ali_AS_TRD_digit*)((*fTRD_digits)[i]) : NULL;
}


	ClassDef(Ali_AS_Track,1);  // A simple track of a particle
};


class Ali_AS_Event : public TObject
{
private:
    Float_t x; // Event vertex x
    Float_t y; // Event vertex y
    Float_t z; // Event vertex z
    Int_t   id; // Run id
    Int_t   N_tracks; // total number of tracks
    Int_t   N_TRD_tracklets; // total number of TRD tracklets
    Float_t   cent_class_ZNA; // ZDC neutral A
    Float_t   cent_class_ZNC; // ZDC neutral C
    Float_t   cent_class_V0A; // V0 A
    Float_t   cent_class_V0C; // V0 C
    Float_t   cent_class_V0M; // V0 average
    Float_t   cent_class_CL0; // clusters in layer 0
    Float_t   cent_class_CL1; // clusters in layer 1
    Float_t   cent_class_SPD; // SPD
    Float_t   cent_class_V0MEq; //
    Float_t   cent_class_V0AEq; //
    Float_t   cent_class_V0CEq; //
    Float_t   ADC_sum_det[540];


    Float_t BeamIntAA; // ZDC coincidence rate
    Float_t T0zVertex; // z-vertex position from VPD

    TString TriggerWord; // Trigger word

    UShort_t      fNumTracks; // number of tracks in event

    TClonesArray* fTracks;      //->

public:
    Ali_AS_Event() :
	x(-1),y(-1),z(-1),id(-1),N_tracks(0),N_TRD_tracklets(0),
	cent_class_ZNA(0),cent_class_ZNC(0),cent_class_V0A(0),cent_class_V0C(0),cent_class_V0M(0),cent_class_CL0(0),cent_class_CL1(0),
        cent_class_SPD(0),cent_class_V0MEq(0),cent_class_V0AEq(0),cent_class_V0CEq(0),BeamIntAA(-1),T0zVertex(-1),TriggerWord(),fNumTracks(0),
        ADC_sum_det()
    {
	fTracks      = new TClonesArray( "Ali_AS_Track", 10 );
    }
	~Ali_AS_Event()
	{
	    delete fTracks;
	    fTracks = NULL;
	}

	void       setx(Float_t r)                    { x = r;                         }
	Float_t    getx() const                       { return x;                      }

	void       sety(Float_t r)                    { y = r;                         }
	Float_t    gety() const                       { return y;                      }

	void       setz(Float_t r)                    { z = r;                         }
	Float_t    getz() const                       { return z;                      }

	void       setid(Int_t  r)                    { id = r;                        }
	Int_t      getid() const                      { return id;                     }

	void       setN_tracks(Int_t r)                 { N_tracks = r;                    }
	Int_t      getN_tracks() const                    { return N_tracks;                 }

	void       setN_TRD_tracklets(Int_t r)                 { N_TRD_tracklets = r;                    }
	Int_t      getN_TRD_tracklets() const                    { return N_TRD_tracklets;                 }

	void       setcent_class_ZNA(Float_t r)             { cent_class_ZNA = r;                }
	Float_t      getcent_class_ZNA() const              { return cent_class_ZNA;             }

	void       setcent_class_ZNC(Float_t r)             { cent_class_ZNC = r;                }
	Float_t      getcent_class_ZNC() const              { return cent_class_ZNC;             }

	void       setcent_class_V0A(Float_t r)             { cent_class_V0A = r;                }
	Float_t      getcent_class_V0A() const              { return cent_class_V0A;             }

	void       setcent_class_V0C(Float_t r)             { cent_class_V0C = r;                }
	Float_t      getcent_class_V0C() const              { return cent_class_V0C;             }

	void       setcent_class_V0M(Float_t r)             { cent_class_V0M = r;                }
	Float_t      getcent_class_V0M() const              { return cent_class_V0M;             }

	void       setcent_class_CL0(Float_t r)             { cent_class_CL0 = r;                }
	Float_t      getcent_class_CL0() const              { return cent_class_CL0;             }

	void       setcent_class_CL1(Float_t r)             { cent_class_CL1 = r;                }
	Float_t      getcent_class_CL1() const              { return cent_class_CL1;             }

	void       setcent_class_SPD(Float_t r)             { cent_class_SPD = r;                }
	Float_t      getcent_class_SPD() const              { return cent_class_SPD;             }

	void       setcent_class_V0MEq(Float_t r)             { cent_class_V0MEq = r;                }
	Float_t      getcent_class_V0MEq() const              { return cent_class_V0MEq;             }

	void       setcent_class_V0AEq(Float_t r)             { cent_class_V0AEq = r;                }
	Float_t      getcent_class_V0AEq() const              { return cent_class_V0AEq;             }

	void       setcent_class_V0CEq(Float_t r)             { cent_class_V0CEq = r;                }
	Float_t      getcent_class_V0CEq() const              { return cent_class_V0CEq;             }

	void       setBeamIntAA(Float_t r)                 { BeamIntAA = r;                      }
	Float_t    getBeamIntAA() const                    { return BeamIntAA;                   }

	void       setT0zVertex(Float_t r)            { T0zVertex = r;                     }
	Float_t    getT0zVertex() const               { return T0zVertex;                  }

	void       setTriggerWord(TString s)          { TriggerWord = s;}
        TString    getTriggerWord() const             { return TriggerWord; }

        void       setADC_sum_det(Int_t i_det, Float_t r) { ADC_sum_det[i_det] = r;}
        ULong64_t  getADC_sum_det(Int_t i_det) const   { return ADC_sum_det[i_det]; }


	Ali_AS_Track* createTrack()
	{
	    if (fNumTracks == fTracks->GetSize())
		fTracks->Expand( fNumTracks + 10 );
	    if (fNumTracks >= 10000)
	    {
		Fatal( "Ali_AS_Event::createTrack()", "ERROR: Too many tracks (>10000)!" );
		exit( 2 );
	    }

	    new((*fTracks)[fNumTracks++]) Ali_AS_Track;
	    return (Ali_AS_Track*)((*fTracks)[fNumTracks - 1]);
	}
	void clearTrackList()
	{
	    fNumTracks   = 0;
	    fTracks      ->Clear();
	}
	UShort_t getNumTracks() const
	{
	    return fNumTracks;
	}
	Ali_AS_Track* getTrack(UShort_t i) const
	{
	    return i < fNumTracks ? (Ali_AS_Track*)((*fTracks)[i]) : NULL;
}

ClassDef(Ali_AS_Event,1);  // A simple event compiled of tracks
};
//----------------------------------------------------------------------------------------



class Ali_AS_analysis_TRD_digits : public AliAnalysisTaskSE
{
public:
    Ali_AS_analysis_TRD_digits()
	: AliAnalysisTaskSE(),
	fDigitsInputFileName("TRD.FltDigits.root"), fDigitsInputFile(0),
	fDigitsOutputFileName(""), fDigitsOutputFile(0),
	fDigMan(0),fGeo(0),AS_Event(0),AS_Track(0),AS_Digit(0),Tree_AS_Event(0), fEventNoInFile(-2), N_good_events(0), fDigitsLoadedFlag(kFALSE),
	h_dca(0x0),h_dca_xyz(0x0),h2D_TPC_dEdx_vs_momentum(0x0),h_ADC_tracklet(0x0)
    {
	cout << "" << endl;
	cout << "***************************************************************************************" << endl;
	cout << "In Ali_AS_analysis_TRD_digits.h constructor" << endl;
	cout << "fDigitsInputFileName: " << fDigitsInputFileName << endl;
	cout << "***************************************************************************************" << endl;
	//AS_Event       = new Ali_AS_Event();
	//AS_Track       = new Ali_AS_Track();
	cout << "" << endl;
    }
	Ali_AS_analysis_TRD_digits(const char *name);
	//virtual ~Ali_AS_analysis_TRD_digits() {}

	virtual void   UserCreateOutputObjects();
	virtual Bool_t UserNotify();
	virtual void   UserExec(Option_t *option);
	virtual void   Terminate(Option_t *);
        void FillHelix(AliESDtrack* track_in, Double_t magF_in);
	void FindDCAHelixPoint(TVector3 space_vec, AliHelix helixA, Float_t path_initA, Float_t path_initB, Float_t &pathA, Float_t &dcaAB);

	void SetDigitsInputFilename(TString x)
	{
	    fDigitsInputFileName=x;
	    cout << "" << endl;
	    cout << "***************************************************************************************" << endl;
	    cout << "fDigitsInputFileName: " << fDigitsInputFileName << endl;
	    cout << "***************************************************************************************" << endl;
	}
	void SetDigitsOutputFilename(TString x) {fDigitsOutputFileName=x;}

	AliHelix aliHelix;

    protected:

	Bool_t NextEvent(Bool_t preload=kFALSE);
	Bool_t ReadDigits();
	Bool_t WriteDigits();
        void   func_tail_cancellation(Short_t *arr, Int_t nexp);


	Int_t FindDigitsTrkl(const AliTRDtrackV1* trdTrack, Int_t layer,
			     Int_t* det, Int_t* row, Int_t* col,
			     Float_t* x, Float_t* y, Float_t* z);

	Int_t FindDigits(const AliExternalTrackParam* param,
			 Float_t bfield, Int_t layer,
			 Int_t* det, Int_t* row, Int_t* col);

	TList           *fListOfHistos;       //! list of output histograms
	TTree           *fTree;               //! output tree
	AliPIDResponse  *fPIDResponse;        //! PID handling
	AliESDtrackCuts *EsdTrackCuts;        //!

    private:

	TFile* OpenDigitsFile(TString inputfile, TString digfile, TString opt);

	TString fDigitsInputFileName;         //! Name of digits file for reading
	TFile*  fDigitsInputFile;             //! Digits file for reading
	TString fDigitsOutputFileName;        //! Name of digits file for writing
	TFile*  fDigitsOutputFile;            //! Digits file for writing

	AliTRDdigitsManager* fDigMan; //! digits manager
	AliTRDgeometry* fGeo; //! TRD geometry
	Ali_AS_Event* AS_Event;
	Ali_AS_Track* AS_Track;
        Ali_AS_TRD_digit* AS_Digit;
	TTree       *Tree_AS_Event;

	Int_t fEventNoInFile;
	Int_t N_good_events;
	Int_t fDigitsLoadedFlag;

	std::vector<TH1D*> h_dca;
	std::vector< std::vector<TH1D*> > h_dca_xyz;
        TH2D* h2D_TPC_dEdx_vs_momentum;
        vector<TH1D*> h_ADC_tracklet;

	Ali_AS_analysis_TRD_digits(const Ali_AS_analysis_TRD_digits&); // not implemented
	Ali_AS_analysis_TRD_digits& operator=(const Ali_AS_analysis_TRD_digits&); // not implemented

	ClassDef(Ali_AS_analysis_TRD_digits, 1);
};



//----------------------------------------------------------------------------------------
class Class_peak_finder
{
    TH1D* TH1D_in;
    Double_t search_width;
    Double_t search_min_diff; // minimum difference between signal and background
    Double_t exclude_width; // range to be excluded between two peaks
    Double_t bin_width;
    Int_t    N_maxima;
    Double_t min_radius;
    Double_t max_width_scan;
    Int_t    flag_peak_rim; // 0 = peak finding, 1 = rim finding
    Int_t    flag_debug = 0; // 1 = return debug output
    TPolyMarker* pm_peaks;
    std::vector< std::vector<Double_t> > vec_peak_positions;
public:
    void  add_TH1D(TH1D* TH1D_in_a);
    void  set_finding_parameters(Int_t flag_peak_rim_in, Double_t search_width_in,
                                 Double_t search_min_diff_in, Double_t exclude_width_in,
                                 Int_t N_maxima_in, Double_t min_radius_in, Double_t max_width_scan_in);
    void  find_peaks();
    TPolyMarker* get_polymarker();
    std::vector< std::vector<Double_t> > get_peak_positions();
    void set_debug(Int_t flag_debug_in);
    void  clear();
};

void Class_peak_finder::set_finding_parameters(Int_t flag_peak_rim_in, Double_t search_width_in,
                                               Double_t search_min_diff_in, Double_t exclude_width_in,
                                               Int_t N_maxima_in, Double_t min_radius_in, Double_t max_width_scan_in)
{
    flag_peak_rim   = flag_peak_rim_in;
    search_width    = search_width_in;
    search_min_diff = search_min_diff_in;
    exclude_width   = exclude_width_in;
    N_maxima        = N_maxima_in;
    min_radius      = min_radius_in;
    max_width_scan  = max_width_scan_in;
}

void Class_peak_finder::add_TH1D(TH1D* TH1D_in_a)
{
    TH1D_in = (TH1D*)TH1D_in_a->Clone("TH1D_in");
    bin_width = TH1D_in->GetBinWidth(1);
    pm_peaks = new TPolyMarker();
}

void Class_peak_finder::find_peaks()
{
    Int_t max_bin = TH1D_in->GetNbinsX();
    Double_t min_val_x = TH1D_in->GetBinCenter(1);
    Double_t max_val_x = TH1D_in->GetBinCenter(max_bin);

    std::vector< std::vector<Double_t> > vec_diff;
    vec_diff.resize(8);

    vec_peak_positions.resize(4); // radial distance, height, density, width

    // Loop over all bins
    for(Int_t i_bin = 1; i_bin <= max_bin; i_bin++)
    {
        Double_t center_val = TH1D_in->GetBinCenter(i_bin);
        Double_t signal_height = TH1D_in->GetBinContent(i_bin);
        Double_t hist_start = TH1D_in->GetBinCenter(1);

        if(center_val < min_radius) continue;

        // Determine search width with maximum density = number of points weighted with Gaussian / Gaussian area
        Double_t max_signal         = 0.0;
        Double_t max_width          = 0.0;
        Double_t max_signal_density = 0.0;
        Double_t max_veto           = 1.0;
        Double_t max_bkgr_left      = 0.0;
        Double_t max_bkgr_right     = 0.0;
        for(Int_t i_search = 0; i_search < 20; i_search++)
        {
            Double_t search_width_scan          = search_width + search_width*i_search;
            Int_t    search_width_scan_bin_half = TH1D_in->FindBin(hist_start + search_width_scan/2.0);

            if(search_width_scan > max_width_scan)
            {
                //printf("i_bin: %d, i_search: %d, search_width_scan: %f, max_width_scan: %f \n",i_bin,i_search,search_width_scan,max_width_scan);
                break;
            }

            Int_t bin_left_bkgr    = i_bin - 2*search_width_scan_bin_half;
            Int_t bin_left_signal  = i_bin - search_width_scan_bin_half;
            Int_t bin_right_signal = i_bin + search_width_scan_bin_half;
            Int_t bin_right_bkgr   = i_bin + 2*search_width_scan_bin_half;

            //printf("i_bin: %d, i_search: %d, bin_width: %d, bins: {%d,%d,%d,%d} \n",i_bin,i_search,search_width_scan_bin_half,bin_left_bkgr,bin_left_signal,bin_right_signal,bin_right_bkgr);

            if(bin_left_bkgr < 1) break;
            if(bin_right_bkgr > max_bin) break;

            // Find minimum value in search range
            Double_t min_val_scan_range = 0.0;
            for(Int_t i_bin_search_min = bin_left_bkgr; i_bin_search_min <= bin_right_bkgr; i_bin_search_min++)
            {
                Double_t bin_cont = TH1D_in->GetBinContent(i_bin_search_min);
                if(bin_cont < min_val_scan_range) min_val_scan_range = bin_cont;
            }

            Double_t sum_signal     = 0.0;
            Double_t sum_bkgr       = 0.0;
            Double_t sum_bkgr_left  = 0.0;
            Double_t sum_bkgr_right = 0.0;
            for(Int_t i_bin_search_min = bin_left_bkgr; i_bin_search_min <= bin_right_bkgr; i_bin_search_min++)
            {
                Double_t bin_cont   = TH1D_in->GetBinContent(i_bin_search_min) - min_val_scan_range;
                if(i_bin_search_min >= bin_left_signal && i_bin_search_min <= bin_right_signal) sum_signal     += bin_cont;
                if(i_bin_search_min >= bin_left_bkgr && i_bin_search_min < bin_left_signal)     sum_bkgr_left  += bin_cont;
                if(i_bin_search_min > bin_right_signal && i_bin_search_min <= bin_right_bkgr)   sum_bkgr_right += bin_cont;
            }
            sum_bkgr = sum_bkgr_left + sum_bkgr_right;

            if(sum_bkgr > sum_signal) continue;
            if(sum_bkgr_left > sum_signal/2.0) continue;
            if(sum_bkgr_right > sum_signal/2.0) continue;
            if(sum_bkgr == 0.0) continue;

            Double_t signal = sum_signal - sum_bkgr;
            Double_t signal_density = signal/search_width_scan;

            //printf("i_bin: %d, i_search: %d, center_val: %f, signal: %f, signal_density: %f,  width: %f \n",i_bin,i_search,center_val,signal,signal_density,search_width_scan);
     

            if(signal_density > max_signal_density)
            {
                max_signal         = signal;
                max_signal_density = signal_density;
                max_width          = search_width_scan;
                max_veto           = 0.0;
                max_bkgr_left      = sum_bkgr_left;
                max_bkgr_right     = sum_bkgr_right;
                //printf("i_bin: %d, i_search: %d, center_val: %f, max_signal: %f, max_signal_density: %f,  max_width: %f \n",i_bin,i_search,center_val,max_signal,max_signal_density,max_width);
            }
        }

        if(max_width <= 0.0) continue;

        /*
        Double_t start_value_background_left  = center_val - max_width/2.0 - max_width/2.0; // half for the peak, half for the background
        Double_t stop_value_background_left   = center_val - max_width/2.0; // half for the peak, left side
        Double_t stop_value_background_right  = center_val + max_width/2.0 + max_width/2.0; // half for the peak, half for the background
        Double_t start_value_background_right = center_val + max_width/2.0; // half for the peak, rigth side

        Int_t bin_bgkr_left_start  = TH1D_in->FindBin(start_value_background_left);
        Int_t bin_bgkr_left_stop   = TH1D_in->FindBin(stop_value_background_left);
        Int_t bin_bgkr_right_start = TH1D_in->FindBin(start_value_background_right);
        Int_t bin_bgkr_right_stop  = TH1D_in->FindBin(stop_value_background_right);

        // Make sure there is some space for the peak
        if(bin_bgkr_left_stop == bin_bgkr_right_start)
        {
            bin_bgkr_left_stop--;
            bin_bgkr_left_start--;
            bin_bgkr_right_start++;
            bin_bgkr_right_stop++;
        }
        if(bin_bgkr_left_start <= 0)       continue;
        if(bin_bgkr_right_stop >= max_bin) continue;


        // Find smallest value in range
        Double_t min_value_range = 0.0;
        for(Int_t i_bin_bkgr = bin_bgkr_left_start; i_bin_bkgr <= bin_bgkr_right_stop; i_bin_bkgr++)
        {
            Double_t bin_cont = TH1D_in->GetBinContent(i_bin_bkgr);
            if(i_bin_bkgr == bin_bgkr_left_start) min_value_range = bin_cont;
            if(bin_cont < min_value_range) min_value_range = bin_cont;
        }

        // Calculate background on the left side
        if(bin_bgkr_left_start == 0)     bin_bgkr_left_start = 1;
        if(bin_bgkr_left_stop > max_bin) bin_bgkr_left_stop  = max_bin;
        Int_t bins_bkgr_left_used = 0;
        Double_t bkgr_left = 0.0;
        for(Int_t i_bin_bkgr = bin_bgkr_left_start; i_bin_bkgr <= bin_bgkr_left_stop; i_bin_bkgr++)
        {
            bkgr_left += TH1D_in->GetBinContent(i_bin_bkgr) - min_value_range;
            bins_bkgr_left_used++;
        }

        // Calculate background on the right side
        if(bin_bgkr_right_start == 0)     bin_bgkr_right_start = 1;
        if(bin_bgkr_right_stop > max_bin) break;
        if(bin_bgkr_right_stop > max_bin) bin_bgkr_right_stop  = max_bin;
        Int_t bins_bkgr_right_used = 0;
        Double_t bkgr_right = 0.0;
        for(Int_t i_bin_bkgr = bin_bgkr_right_start; i_bin_bkgr <= bin_bgkr_right_stop; i_bin_bkgr++)
        {
            bkgr_right += TH1D_in->GetBinContent(i_bin_bkgr) - min_value_range;
            bins_bkgr_right_used++;
        }

        // Calculate total average background
        //printf("min_value_range: %f, bkgr: {%f,%f}, used bins: {%d,%d} \n",min_value_range,bkgr_left,bkgr_right,bins_bkgr_left_used,bins_bkgr_right_used);
        Double_t bkgr_total = bkgr_left + bkgr_right;
        Int_t bins_bkgr_total_used = bins_bkgr_left_used + bins_bkgr_right_used;
        if(bins_bkgr_total_used > 0)
        {
            bkgr_total /= (Double_t)(bins_bkgr_total_used);
        }

        // Calculate total signal
        Int_t bin_peak_left  = bin_bgkr_left_stop   + 1;
        Int_t bin_peak_right = bin_bgkr_right_start - 1;
        if(bin_peak_left == 0)  bin_peak_left = 1;
        if(bin_peak_right > max_bin)  bin_peak_right = max_bin;
        Int_t bins_peak_used = 0;
        Double_t peak_total = 0.0;
        for(Int_t i_bin_peak = bin_peak_left; i_bin_peak <= bin_peak_right; i_bin_peak++)
        {
            peak_total += TH1D_in->GetBinContent(i_bin_peak) - min_value_range;
            bins_peak_used++;
        }
        if(bins_peak_used > 0)
        {
            peak_total /= (Double_t)bins_peak_used;
        }

        //if(flag_debug) printf("i_bin: %d, x_pos: %f, max_width: %f, peak_total: %f, bkgr_total: %f,  min_value_range: %f, bin_bgkr_left: {%d,%d}, bin_bgkr_right: {%d,%d}, bin_peak: {%d,%d} \n",i_bin,center_val,max_width,peak_total,bkgr_total,min_value_range,bin_bgkr_left_start,bin_bgkr_left_stop,bin_bgkr_right_start,bin_bgkr_right_stop,bin_peak_left,bin_peak_right);


        // Veto peak if left or right side background is larger than signal
        Int_t veto_bkgr = 0;
        if(bins_bkgr_left_used > 0)
        {
            bkgr_left /= (Double_t)bins_bkgr_left_used;
            if(bkgr_left > peak_total) veto_bkgr = 1.0;
        }
        if(bins_bkgr_right_used > 0)
        {
            bkgr_right /= (Double_t)bins_bkgr_right_used;
            if(bkgr_right > peak_total) veto_bkgr = 1.0;
        }

        Double_t diff_peak_bkgr = 0.0;
        if(bkgr_total > 0.0)
        {
            diff_peak_bkgr = (peak_total - bkgr_total)/(bkgr_total);
        }
        if(bkgr_total == 0.0)
        {
            diff_peak_bkgr = peak_total;
            cout << "WARNING in Class_peak_finder::find_peaks: bkgr_total == 0.0: " << bkgr_total << endl;
        }
        */

        vec_diff[0].push_back(center_val);
        vec_diff[1].push_back(signal_height);
        vec_diff[2].push_back(max_signal_density);
        vec_diff[3].push_back(max_signal);
        vec_diff[4].push_back(max_veto);
        vec_diff[5].push_back(max_bkgr_left);
        vec_diff[6].push_back(max_bkgr_right);
        vec_diff[7].push_back(max_width);

        //if(flag_debug) printf("i_bin: %d, center_val: %f, S/B: %f, peak_total: %f, bkgr_left: %f, bkgr_right: %f \n",i_bin,center_val,diff_peak_bkgr,peak_total,bkgr_left,bkgr_right);
    } // end of histogram bin loop

    // Find all maxima, exclude ranges within exclude_width after each loop
    Int_t max_i_diff = 0;
    while(max_i_diff >= 0 && vec_diff[0].size() > 0)
    {
        Double_t best_center_val     = 0.0;
        Double_t best_signal_height  = 0.0;
        Double_t best_signal_density = 0.0;
        Double_t best_signal         = 0.0;
        Double_t best_bkgr_left      = 0.0;
        Double_t best_bkgr_right     = 0.0;
        Double_t best_width          = 0.0;

        max_i_diff = -1;
        if(flag_peak_rim == 0) // peak finding
        {
            // Find maximum signal to background above minimum defined
            for(Int_t i_diff = 0; i_diff < vec_diff[0].size(); i_diff++)
            {
                //printf("   i_diff: %d, S/B: %f, veto: %f \n",i_diff,vec_diff[1][i_diff],vec_diff[3][i_diff]);
                if(vec_diff[2][i_diff] > best_signal_density
                   //&& vec_diff[1][i_diff] >= search_min_diff
                   && vec_diff[4][i_diff] < 1.0)
                {
                    // Check if this point with its width is already in range of a previously found point
                    // Avoid peaks on top of peaks
                    Int_t flag_in_range_of_accepted_point = 0;
                    for(Int_t i_already_accepted_point = 0; i_already_accepted_point < vec_peak_positions[0].size(); i_already_accepted_point++)
                    {
                        Double_t acc_center       = vec_peak_positions[0][i_already_accepted_point];
                        Double_t this_point_width = vec_diff[7][i_diff];

                        if(fabs(vec_diff[0][i_diff] - acc_center) < this_point_width)
                        {
                            flag_in_range_of_accepted_point = 1;
                            vec_diff[4][i_diff] = 1.0; // veto this point
                        }
                    }

                    if(!flag_in_range_of_accepted_point)
                    {
                        best_center_val     = vec_diff[0][i_diff];
                        best_signal_height  = vec_diff[1][i_diff];
                        best_signal_density = vec_diff[2][i_diff];
                        best_signal         = vec_diff[3][i_diff];
                        best_bkgr_left      = vec_diff[5][i_diff];
                        best_bkgr_right     = vec_diff[6][i_diff];
                        best_width          = vec_diff[7][i_diff];
                        max_i_diff          = i_diff;
                        //if(flag_debug) printf("    -> peak found at x_pos: %f",max_diff_x);
                    }
                }
            }
        }
        else // rim finding
        {
            /*
            // Find maximum signal to background above minimum defined
            for(Int_t i_diff = 0; i_diff < vec_diff[0].size(); i_diff++)
            {
                Double_t slope_left  = vec_diff[2][i_diff] - vec_diff[4][i_diff];
                Double_t slope_right = vec_diff[5][i_diff] - vec_diff[2][i_diff];

                Double_t slope_change = fabs(slope_right - slope_left);
                if(1)
                {
                    //printf("max_i_diff: %d, heights: {%f,%f,%f}, slopes: {%f,%f}, slope_change: %f \n",max_i_diff,vec_diff[4][i_diff],vec_diff[2][i_diff],vec_diff[5][i_diff],slope_left,slope_right,slope_change);
                    if(slope_change > max_diff &&  slope_change > search_min_diff)
                    {
                        max_diff_x = vec_diff[0][i_diff];
                        max_diff   = slope_change;
                        max_height = vec_diff[2][i_diff];
                        max_i_diff = i_diff;
                    }
                }
            }
            */
        }

        if(best_width > exclude_width) exclude_width = best_width;

        // Find range within exclude_width to be erased
        Int_t i_diff_left_erase = 0;
        for(Int_t i_diff = max_i_diff; i_diff >= 0; i_diff--)
        {
            if(fabs(best_center_val - vec_diff[0][i_diff]) > exclude_width)
            {
                i_diff_left_erase = i_diff;
                break;
            }
        }

        Int_t i_diff_right_erase = vec_diff[0].size();
        for(Int_t i_diff = max_i_diff; i_diff <= vec_diff[0].size(); i_diff++)
        {
            if(fabs(best_center_val - vec_diff[0][i_diff]) > exclude_width)
            {
                i_diff_right_erase = i_diff;
                break;
            }
        }


        //cout << "start erase: "<<  i_diff_left_erase << ", stop erase: " << i_diff_right_erase << endl;
      
        if(max_i_diff >= 0)
        {
            //printf("polymarker set at: %f, height: %f \n",best_center_val,best_signal_height);
            pm_peaks ->SetNextPoint(best_center_val,best_signal_height);
            vec_peak_positions[0].push_back(best_center_val);
            vec_peak_positions[1].push_back(best_signal_height);
            vec_peak_positions[2].push_back(best_signal_density);
            vec_peak_positions[3].push_back(best_width);

            if(flag_debug) printf("max_i_diff: %d, x,height: {%f,%f}, best_density: %f, best_width: %f, S,Lbkgr,Rbkgr: {%f,%f,%f} \n",max_i_diff,best_center_val,best_signal_height,best_signal_density,best_width,best_signal,best_bkgr_left,best_bkgr_right);

            //cout << "max_diff_x: " << max_diff_x << ", max_diff: " << max_diff << ", max_i_diff: " << max_i_diff << ", size: " << vec_diff[0].size()
            //    << ", peak_total: " << vec_diff[2][max_i_diff] << ", bkgr_left: " << vec_diff[4][max_i_diff] << ", bkgr_right: " << vec_diff[5][max_i_diff] << endl;

        }

        if(vec_peak_positions[0].size() >= N_maxima) break;

        vec_diff[0].erase(vec_diff[0].begin() + i_diff_left_erase, vec_diff[0].begin() + i_diff_right_erase);
        vec_diff[1].erase(vec_diff[1].begin() + i_diff_left_erase, vec_diff[1].begin() + i_diff_right_erase);
        vec_diff[2].erase(vec_diff[2].begin() + i_diff_left_erase, vec_diff[2].begin() + i_diff_right_erase);
        vec_diff[3].erase(vec_diff[3].begin() + i_diff_left_erase, vec_diff[3].begin() + i_diff_right_erase);
        vec_diff[4].erase(vec_diff[4].begin() + i_diff_left_erase, vec_diff[4].begin() + i_diff_right_erase);
        vec_diff[5].erase(vec_diff[5].begin() + i_diff_left_erase, vec_diff[5].begin() + i_diff_right_erase);
        vec_diff[6].erase(vec_diff[6].begin() + i_diff_left_erase, vec_diff[6].begin() + i_diff_right_erase);
        vec_diff[7].erase(vec_diff[7].begin() + i_diff_left_erase, vec_diff[7].begin() + i_diff_right_erase);
    }
}

TPolyMarker* Class_peak_finder::get_polymarker()
{
    return pm_peaks;
}

std::vector< std::vector<Double_t> > Class_peak_finder::get_peak_positions()
{
    return vec_peak_positions;
}

void Class_peak_finder::set_debug(Int_t flag_debug_in)
{
    flag_debug = flag_debug_in;
}

void Class_peak_finder::clear()
{
    delete pm_peaks;
    vec_peak_positions.clear();
    delete TH1D_in;
}
//----------------------------------------------------------------------------------------




#endif
