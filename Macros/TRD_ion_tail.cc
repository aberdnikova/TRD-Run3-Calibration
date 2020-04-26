
#include "TRD_ion_tail.h"

void TRD_ion_tail()
{
    printf("TRD_ion_tail started, all systems nominal. \n");

    Load_data();

    tg_pad_response ->Draw();

    Double_t impact_angle             = 75.0;
    Double_t Lorentz_angle            = -17.5;
    Double_t Drift_vel_ratio          = 1.2; // 0.8
    Double_t Lorentz_angle_pre_corr   = -10; // -7.5

    Draw_TRD_detector_2D();
    Create_TRD_track(impact_angle*TMath::DegToRad(),Lorentz_angle*TMath::DegToRad(),Drift_vel_ratio,Lorentz_angle_pre_corr*TMath::DegToRad());
    Make_ion_tail_convolution();
    Create_TRD_track(impact_angle*TMath::DegToRad(),Lorentz_angle*TMath::DegToRad(),Drift_vel_ratio,Lorentz_angle_pre_corr*TMath::DegToRad());
    Reconstruct_tracklet();


}