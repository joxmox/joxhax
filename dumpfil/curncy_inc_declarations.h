// Currency File - CURNCY.IND
//!
MapStringItem curncy_CodeS;   //Primary Key-Currency Code
MapStringItem curncy_Shrt_NameS;   //Alt Key-Currency Short Name
MapStringItem curncy_NameS;    //Currency Name
MapStringItem curncy_Swift_CodeS;   //Swift Currency Code
//Alternate key
MapStringItem curncy_Rec_FlagS;
MapSimpleItem<int16_t> curncy_Rate_UnitI;
MapSimpleItem<int16_t> curncy_Decimal_PlacesI;   //Decimal 0 = no decimal
// 	 2 = 2 decimals
//allowed 0-4
MapSimpleItem<double> curncy_Cross_Rate;  //Cross rate for reporting cur
MapStringItem curncy_Main_Curr_FlagS;    //for std-oil only
//main currency (Y/N)
MapStringItem curncy_Msa_FlagS;  //Mixed stradels accounts
MapStringItem curncy_Date_Lst_Update1S;   //Currency Entry date
MapSimpleItem<double> curncy_Spot_Rate;    //Spot rate
MapStringItem curncy_Date_Lst_Update2S;   //Last Update date
MapSimpleItem<double> curncy_Fix_Rate;   //Daily Fixing Rate Sale
MapStringItem curncy_Date_Lst_Update3S;   //Last Update date
MapSimpleItem<double> curncy_Fix_Margin;   //Daily Fixing MARGIN
MapStringItem curncy_Date_Lst_Update4S;   //Last Update date
MapStringItem curncy_Local_CodeS;  //Code for the currency locally
MapSimpleItem<double> curncy_Usd_Spot_Rate;  //Spot rate - curncy to USD
// Always stored multiplicative
MapStringItem curncy_Usd_Date_Lst_UpdtS;   //USD spot rate Update
MapStringArray<1> curncy_Nonres_Float_FlagSA;   //this is for lux
//only, 0 = doesn't exit
//      1 = exists
//branch information
//
MapStringArray<8> curncy_Def_NosSA;     //Index is Branch Code
//consider reorganizing this out
//of array section in release 3
MapSimpleItem<int16_t> curncy_Eec_CodeI;    //EEC code
MapSimpleItem<double> curncy_Euro_Rate;  //Fixed rate against EURO
MapStringItem curncy_Emu_MemberS;   //EMU member, Y/N
MapSimpleItem<double> curncy_Euro_Spot_Rate;     //
MapStringItem curncy_Ext_Pos_AccntS;  // External appl pos acct
MapStringItem curncy_Cutoff_TimeS;   // Currency cut-off time
MapSimpleItem<double> curncy_Fix_Year_Rate;  // Fixed year rate WAR only
MapStringItem curncy_Psd_MemberS;   //SEPA PSD member, Y/N
//
MapSimpleItem<double> curncy_Fee_Percentage;  //used for calculating the
//negative fee at month end.
MapSimpleItem<double> curncy_Threshold;  //amount valid for the currency.
MapStringItem curncy_Calc_FlagS;  //Actual for negative rate calc.
//
MapStringItem curncy_Loc_Clr_MemberS;  //Local Clearing Member, Y/N
//
MapStringArray<8> curncy_Int_Float_DdaSA;    //Internal dda used for
//cross value date deals
MapStringArray<8> curncy_PrSA;    //P & R NUMBER (Nostro)
MapStringArray<20> curncy_Control_NosSA;
MapStringArray<20> curncy_Control_VosSA;
MapStringItem cur_CodS;
MapStringItem cur_Sht_NamS;
MapStringItem cur_NamS;
MapStringItem cur_Swift_CodS;
MapStringItem cur_Rec_FlagS;
MapSimpleItem<int16_t> cur_Rate_UnitI;
MapSimpleItem<double> cur_Spot_Rate;
MapStringItem cur_Dat_LastupdatS;
MapStringItem curncy_AllS;
MapArray<Glno_rec> curncy_Control_NosA;
MapArray<Glno_rec> curncy_Control_VosA;
