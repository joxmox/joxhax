//
// File name   : Commercial Loan Data File
// File spec   : CLFILE:CLLOAN.IND
// File type   : Indexed
// 		Primary Key LOAN.NO$,
//		Alternate Key LOAN.CUST.NO$ DUPLICATES,
//		Alternate Key LOAN.ISS.DATE$ DUPLICATES,
//		Alternate Key LOAN.MAT.DATE$ DUPLICATES CHANGES
//		Alternate Key LOAN.PRTCP.NO$ DUPLICATES CHANGES
// File freq   : Permanent
// Record desc : Fixed
//      Length : 956 bytes
// Date        : 30-JULY-1986
// Author      : AMER ELMOURAD
// Description : Containe all information about the loan
//		It gets updated on line and during the E.O.D
//
// Revision History:
// 1-16-96	Louis Quintana   Adding Sebtrade number field.
//
//
//---------------------------------------------------------------
//
MapStringItem loan_NoS;       //Loan number - right justified zero fill
MapStringItem loan_Tr_Seq_NoS;       //Sequence number of last processed trans
//  right justified zero fill
MapStringItem loan_Rec_FlagS;    //Record-in-use flag: 1 -> free; 2 -> in use
MapStringItem loan_Op_IndS;   //Operator ID from last processed transaction
MapStringItem loan_Dep_NoS;    //Department No. from operator control table
MapStringItem loan_Unit_NoS;       //Unit Number from operator control table
MapStringItem loan_Gl_Ac_NoS;       //Principal General Ledger account number
//Key to accounting table
//Right justified space fill
//R3 - Profit Center GL #
MapStringItem loan_Ass_Lib_FlS;             //Asset - Liability indicator (A/L)
MapStringItem loan_CurrS;    //Currency code - right justified space fill
MapStringItem loan_Sec_IndS;               //Secured indicator:
//U -> Unsecured
//S -> Secured
//P -> Partially Secured
MapStringItem loan_Mat_DateS;       //Maturity date - IBIS packed date format
//CHR$(255) for demand loans
MapSimpleItem<double> loan_Tenor;   //Loan tenor - double precision (8 byte) real
MapSimpleItem<double> loan_Amount;                //Loan amount -- source currency
//double precision (8 byte) real
MapSimpleItem<double> loan_Eq_Amount;       //Loan equivalent amount -- base currency
//double precision (8 byte) real
MapSimpleItem<double> loan_Conv_Rate;                   //Loan conversion (spot) rate
//double precision (8 byte) real
MapStringItem loan_Cust_NoS;  //Customer number - right justified space fill
MapStringItem loan_Conv_Rate_RecpS;         //'R' if LOAN.CONV.RATE is reciprical
MapStringItem loan_Tr_DateS;  //Loan transaction date (date of loan agrement
//IBIS packed date format
MapStringItem loan_Iss_DateS;           //Loan issue date (drawdown date)
//IBIS packed date format
MapSimpleItem<double> loan_Int_Rate;           //Interest rate for fix rate loans
//Spread for floating rate loans
//double precision (8 byte) real
MapStringItem loan_Int_Rat_BasS;          //Interest calculation year base code:
// 1 -> 360 day year
// 2 -> 365 day year
// 3 -> 366 day year
// 4 -> 30/360-30 days per month, 360 per year
MapStringItem loan_Ff_IndS;          //Federal funds code (CIF table)
MapSimpleItem<double> loan_Dal_Int_Accr;           //Daily interest accrual amount
//double precision (8 byte) real
//unrounded except for discount loans
MapSimpleItem<double> loan_Tot_Int_Due;         //Total interest due (fixed rate loans)
//double precision (8 byte) real
//This is actually total interest on the loan,
//not reduced by interest paid.
//LOAN.NEG.INT.ADJ.AMT is included.
MapStringItem loan_Int_Pay_FrS;                    //Interest payment frequency
// 1 - 98 -> number of months between payments
//     99 -> due at maturity
MapStringItem loan_Int_Pay_DayS;          //Interest payment day (day of month)
MapStringItem loan_Prin_Pay_FrS;              //Principal payment frequency
// 1 - 98 -> number of months between payments
//     99 -> due at maturity
MapStringItem loan_Prin_Pay_DayS;          //Principal payment day (day of month)
MapStringItem loan_BranchS;             //Branch code
MapStringItem loan_Internal_CodeS;         //Field for site-specific coding
MapStringItem loan_Off_Balance_IndS;          //Off balance sheet indicator
MapStringItem loan_OfficerS;      //Loan officer (CIF account manager table)
MapStringItem loan_Roll_IndS;               //Rollover indicator:
// Y -> rollover loan
// N -> no rollover
MapStringItem loan_Rec_IndS;               //
MapStringItem loan_Ref_Line1S;              //2 lines of free text
MapStringItem loan_Ref_Line2S;                         //for reference only
MapStringItem loan_Fiduc_Deposit_IndS;  //= F IF Fiduciary drawn against a Deposit
//= D If it is a deposit loan tied to a Fid.
MapStringItem loan_Mat_Int_Settl_IndS;     //Flag to indicate if interest maturity
//instructions exist (Y/N)
MapStringItem loan_Mat_Settl_IndS;    //Flag to indicate if principal maturity
//instructions exist (Y/N)
MapSimpleItem<int16_t> loan_Decimal_PlacesI;          //Loan currency decimal places
MapStringItem loan_Cont_CountS;            //Number of hedge contracts for loan
MapSimpleItem<double> loan_Var_Rate;           //Variable interest rate
//double precision (8 byte) real
MapStringItem loan_Rate_TypeS;             //Interest rate type:
// 1 -> fix rate loan
// 2 - 99 -> variable rate type
//           as defined by floating rate table
MapStringItem loan_Perc_IndS;           //Percentage indicator :
//P->LOAN.INT.RATE used as % of LOAN.VAR.RATE
//other- LOAN.INT.RATE added to  LOAN.VAR.RATE
MapStringItem loan_Repay_TypeS;           //Loan repayment type code:
// 1 - Separate principal and interest
// 2 - Single payment (mortgage type)
MapStringItem loan_Libor_Exp_DateS;              //Interest rate expiry date
//IBIS packed date format
MapStringItem loan_Int_Paid_To_DateS;                //Interest paid-to date
//IBIS packed date format
MapSimpleItem<double> loan_Secured_Amount;           //Secured amount on loan
MapSimpleItem<double> loan_Margin;   //Margin percent used by Landerbank
MapSimpleItem<double> loan_Unearned_Disc_Amt;    //Unearned discount amount for discount loan
MapSimpleItem<double> loan_Net_Proceed_Amt;    //Net proceeds (ie. issue settlement amount)
//for discount loan (8 byte real)
MapSimpleItem<double> loan_Neg_Int_Adj_Amt;        //Total amount of negative interest adj.
//stored as absolute value. This must be added
//to the amount paid when using int paid to
//calculate amount due.
MapSimpleItem<int16_t> loan_Roll_Inst_EntI;        //set to -1 if rollover instruction have
//been entered for rollover coming due. This
//is cleared on rollover date.
MapStringItem loan_Roll_Issue_DateS;     //Issue date of rollover, or issue date of
//non-rollover loan. This is used to check
//the oldest allowable back value date.
MapSimpleItem<double> loan_Original_Amount;    //Original amount of loan in source currency
MapSimpleItem<double> loan_Original_Eq_Amount;      //Original amount of loan in base currency
MapSimpleItem<double> loan_Comm_Amount;          //Commission amount  (8 byte real)
MapSimpleItem<double> loan_Daily_Dissagio_Amount;                    //
MapStringItem loan_Comm_Lim_NumberS;             //Commitment / Line number
MapStringItem loan_Profit_CtrS;            //Profit Center code (CIF table)
MapStringItem loan_Accr_CodeS;                    //Accrual Code:
// A -> regular accrual
// C -> Discount Loan
// D -> Call loan
MapStringItem loan_Fed_ClassS;       //Federal Classification code (CIF table)
MapStringItem loan_TypeS;         //loan type (r3)
MapStringItem loan_Guar_IndS;           //Guarantor indicator (Y/N)
MapStringItem loan_StatusS;                            //Loan Status:
// 1 -> Future
// 2 -> Open
// 3 -> Matured
// 4 -> Interest Settled
// 5 -> Principal Settled
// 6 -> Matured and Settled
// 7 -> Reversed
MapStringItem loan_Iss_Cable_Sent_IndS;   // INDICATOR TO SHOW IF CABLE SENT FOR
// LOAN ISSUE Y = SENT	N = NOT SENT
MapStringItem loan_Int_Cable_Sent_IndS;     // INTEREST CABLE INDICATOR AS ABOVE
// FLAG IS SET WHEN A MESSAGE IS SENT TO
// MT AND CLEARED WHEN THE ACCTG IS DONE
MapStringItem loan_Prin_Cable_Sent_IndS;   // PRINCIPALE CABLE INDICATOR AS ABOVE
MapSimpleItem<double> loan_Demand_Past_Due_Amt;        // FOR DEMAND LOANS INTEREST ONLY
MapStringItem loan_Demand_Prior_Due_DateS;            //
MapStringItem loan_Demand_Next_Due_DateS;            //
MapSimpleItem<int16_t> loan_Mt_Doc_NoI;          // SEQUENCE NO FOR MT INTERFACE
MapSimpleItem<int16_t> loan_Mt_Doc_Rev_NoI;          //    "     "   "  "   REVERSAL
//
MapStringItem loan_Comm_CurrencyS;        //Commitment currency from clhskp
MapSimpleItem<double> loan_Comm_Rate;     //Commitment to loan conversion rate
MapStringItem loan_Comm_Rate_RecpS;         //'R' if comm rate is reciprocal
MapStringItem loan_MailS;         //'Y' to mail confirm/bills
MapStringItem loan_RefiS;             //Loan funding code (not validated)
MapStringItem loan_Security_CodeS;            //Loan security code (not validated)
MapStringItem loan_Rollover_DateS;                 //Loan rollover date
//IBIS packed date format
MapStringItem loan_Prtcp_IndS;      //Flag to indicate if loan is participated
// Y => particapation
// N => no participation
MapStringItem loan_Prtcp_RecourseS;              //Participation recourse indicator
//1= with recourse. 'Y' on the pymt. screen.
//   ignored by commitment rebuild and ITC
//2= without recourse. 'N' on pymt. screen
//   Increases Remaining amount on commitment
//   when a part. Loan is entered.  Decreases
//   Remaining amt. when part. Loan payed off
MapStringItem loan_Auto_Prin_PymtS;     //Automatic principal payments (during EOD)
//Y = yes
//N = manual settlement
MapStringItem loan_Auto_Int_PymtS;      //Automatic Interest payments (during EOD)
//Y = yes
// N= manual settlement
MapStringItem loan_Auto_Prin_Pay_DateS;   //Date of next automatic principal pymt.
//IBIS packed date format
MapStringItem loan_Auto_Int_Pay_DateS;    //Date of next automatic interest pymt.
//IBIS packed date format
MapSimpleItem<double> loan_Dissagio_Amount;          // Amortized Commission Amount
MapStringItem loan_Dissagio_IndS;          //	Y= YES 		N= NO
MapStringItem loan_Fiduciary_IndS;     //TO show if the loan is a Fiduciary loan
MapStringItem loan_Prtcp_Cust_NoS;          //Customer number of asset loan for
//sub participations
MapStringItem loan_Prtcp_NoS;      //Asset loan number for sub participations
//This is also used for Deposit number
MapStringItem loan_Begin_DateS;          // Variant 2 Option (DSB)
MapStringItem loan_End_DateS;             //
MapStringItem loan_Local_SicS;             //
MapStringItem loan_Cost_TypeS;             //
MapStringItem loan_Gross_IndS;             //
MapStringItem loan_Cost_CenterS;     //Converting Midas to IBIS - Frankfurt only
//was LOAN.LAST.NOTE.PAID% - not used
//    LOAN.INT.NOTE.PAID%
MapSimpleItem<double> loan_Accr_Int_Rec;     //Accrued interest recievable (8 byte rea l
//rounded accrued amount less interest paid
//This is the amount of interest due on the
//loan as of today.
//LOAN.NEG.INT.ADJ.AMT is included.
MapSimpleItem<double> loan_Tot_Int_Rec;         //Total interest received (8 byte real)
//not including LOAN.NEG.INT.ADJ.AMT
MapSimpleItem<double> loan_Ytd_Int_Rec;  //Year to date interest received (8 byte real)
MapStringItem loan_Dat_Last_AccrS;        //Date of last accrual (accrual to-date)
//IBIS packed date format
MapStringItem loan_Dat_Ls_Int_PayS;          //Date of last interest payment
//IBIS packed date format
MapStringItem loan_Risk_ClassS;    //Risk Class code defined on std codes table
MapStringItem loan_Date_SetS;     //Loan set up date (date entered on system)
//IBIS packed date format
MapStringItem loan_Payoff_DateS;                     //Date of loan payoff
//IBIS packed date format
MapSimpleItem<double> loan_Acc_Todate;    //Accrued interest to date (source currency)
//8 byte real number. rounded - not less
//interest paid.
//LOAN.NEG.INT.ADJ.AMT is included.
MapSimpleItem<double> loan_Acc_Todate_Eqv;    //Accrued interest to date equivalent (base)
//8 byte real number
MapSimpleItem<double> loan_Tot_Int_Rec_Eqv;
MapStringItem loan_Ls_Acct_DateS;             //Date of last transaction for loan
//IBIS packed date format
MapSimpleItem<double> loan_Dissagio_Acc_Todate; //Amortized Commission Amount accrued todat
MapStringItem loan_Sebtrade_NoS;           //Sebtrade number
//was LOAN.CURR.PERIOD.COMM.INC
//    LOAN.PREV.PERIOD.COMM.INC
//was LOAN.DAILY.PREM.DISC.AMOUNT
//but not used, discounted loans use
//LOAN.DAL.INT.ACCR for daily factor
MapSimpleItem<double> loan_Earned_Disc_Amt;                 //Earned discount amount
MapSimpleItem<double> loan_Last_Auto_Int_Tax;  //Tax withheld on last int payment if liab
//    LOAN.PREV.PERIOD.INT.INC
//    LOAN.CURR.PERIOD.INT.INC
MapSimpleItem<double> loan_Last_Auto_Prin_Amt;      //Amount of last auto. prin. pay to MT
MapSimpleItem<double> loan_Last_Auto_Int_Amt;   //Amount of last auto. interest pay to MT
//not reduced by tax withheld
MapStringItem loan_Dat_Last_Rate_ChngS;         //Date of last interest rate change
//or last libor rate expiration date if
//rate didn't change.
//IBIS packed date format
MapStringItem loan_Dat_Last_Prnc_ChngS;             //Date of last princiapl change
//IBIS packed date format
MapStringItem loan_Last_Auto_Prin_DateS;     //Date of last auto. principal payment
//sent to MT.
MapStringItem loan_Last_Auto_Int_DateS;  //Date of last auto.interest payment to MT
// (was LOAN.LAST.YTD.ACC.TODATE
// and LOAN.INT.RECEIVABLE% and
// LOAN.PRINC.RECEIVABLE%)
MapSimpleItem<double> loan_Curr_Period_Dollar_Days;   //Aggregate principal for current month
MapSimpleItem<double> loan_Prev_Period_Dollar_Days;  //Aggregate principal for previous month
MapSimpleItem<double> loan_Princ_Receivable;        //Past due principal (according to notes)
//Includes interest if mortgage note
MapSimpleItem<double> loan_Int_Receivable;        //Past due interest  (according to notes)
//actually - total interest accrued-unrounded
//not less interest paid.
//LOAN.NEG.INT.ADJ.AMT is included.
MapSimpleItem<double> loan_Ytd_Dollar_Days;         // Aggregate principal for year to date
MapSimpleItem<double> loan_Curr_Per_Disc_Int_Ear;          //Aggregate interest on loans for
//	current month - not just discounted
MapSimpleItem<double> loan_Int_Payoff_Amt;             //
MapSimpleItem<double> loan_Prev_Per_Disc_Int_Ear;          //Aggregate interest on loans for
//	previous month - not just discounted
MapSimpleItem<double> loan_Ytd_Disc_Int_Ear;          //Aggregate interest on loans for
//	year to date	not just discounted
MapStringItem loan_Date_Last_Int_DueS;      //Set to last interest note due during
//billing.
MapSimpleItem<double> loan_Tax_Todate;    //int acrruals reported to cftax to date
// was LOAN.RISK.PARTA$=89%
MapStringItem loan_Gl_brS;            // Branch code
MapStringItem loan_Reclass_DateS;    // Date of the last TYPE CHANGE for loan
MapStringItem loan_Dem_Prin_Prior_Due_DateS;      //	For demand loans principal
MapStringItem loan_Dem_Prin_Next_Due_DateS;           //
MapSimpleItem<double> loan_High_Comm_Amount; // Highest loan original amount in comm cur
//
MapSimpleItem<double> loan_Security_Perc;
MapSimpleItem<int16_t> loan_Pos_WeightI;
MapStringItem loan_Actual_Rate_Chg_DateS;         //Date of last actual rate change
//This date will correspond to a record in
//the history file.
MapSimpleItem<double> loan_Tax_With_Perc;
MapStringItem loan_Tax_With_IndS;
MapStringItem loan_AssignmentS;
MapStringItem loan_Cc2_CodeS;
MapStringItem loan_WikindS;    // WIK Loan indcator Y or N
MapStringItem loan_Iblc_Std_FlagS; //The next 5 variable are for lux
MapStringItem loan_Iss_Principal_Iblc_CodeS;
MapStringItem loan_Mat_Principal_Iblc_CodeS;
MapStringItem loan_Iss_Sett_Iblc_CodeS;
MapStringItem loan_Mat_Sett_Iblc_CodeS;
MapStringItem loan_Int_Iblc_CodeS;
MapStringItem loan_Auth_OfficerS;      //Auth.officer (CIF account manager table)
MapSimpleItem<int16_t> loan_Billing_DaysI;
MapSimpleItem<double> loan_Collateral_Req_Minimum;
MapSimpleItem<double> loan_Collateral_Value;
MapStringItem loan_Collateral_Reval_DateS;
//MAP FOR CL  LOAN
MapStringItem loan_EverythingS;
MapStringItem loan_AllS;
MapStringItem loan_Misc1S;
MapRecordItem<Glno_rec> loan_Gl;
MapRecordItem<Ityp_rec> loan_Typ;
