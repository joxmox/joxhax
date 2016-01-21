#ifndef CLMAP_CLLOAN650_REC_TYPES
#define CLMAP_CLLOAN650_REC_TYPES

#pragma pack(push)
#pragma pack(1)
class Clloan_rec : public RecordTemplate<Clloan_rec>
{
public:
	Variant
	{
		Case
		{
			StringField<11> loan_No;      //Loan number - right
			//just. zero fill
			StringField<5> loan_Tr_Seq_No;       //Sequence number of
			//last processed trans
			//right just. zero fill
			StringField<1> loan_Rec_Flag;      //Record-in-use flag:
			//1 -> free; 2 -> in use
			StringField<4> loan_Op_Ind;    //Operator ID from last
			//processed transaction
			StringField<4> loan_Dep_No;      //Department No. from
			//operator control table
			StringField<4> loan_Unit_No;        //Unit Number from
			//operator control table
			StringField<20> loan_Gl_Ac_No;    //Principal  GL accT no
			//Key to accounting table
			//Right just. space fill
			StringField<1> loan_Ass_Lib_Fl;     //Ass - Liab ind (A/L)
			StringField<3> loan_Curr;   //ccy code - right just.
			//space fill
			StringField<1> loan_Sec_Ind;       //Secured indicator:
			//U -> Unsecured
			//S -> Secured
			//P -> Partially Secured
			StringField<6> loan_Mat_Date;       //Maturity date
			DoubleField loan_Tenor;        //Loan tenor
			DoubleField loan_Amount;              //Loan amount
			DoubleField loan_Eq_Amount;   //Loan equivalent amount
			DoubleField loan_Conv_Rate;   //Loan conv. (spot) rate
			StringField<13> loan_Cust_No;       //Customer number
			StringField<1> loan_Conv_Rate_Recp;    //'R' if LOAN.CONV.RATE
			//is reciprical
			StringField<6> loan_Tr_Date;       //Loan trans. date
			//(date of loan agrement
			//IBIS packed date format
			StringField<6> loan_Iss_Date;       //Loan issue date
			//(drawdown date)
			//IBIS packed date format
			DoubleField loan_Int_Rate;       //Interest rate for
			//fix rate loans
			//Spread for floating
			//rate loans
			StringField<1> loan_Int_Rat_Bas;     //Interest calculation
			//year base code:
			// 1 -> 360 day year
			// 2 -> 365 day year
			// 3 -> 366 day year
			// 4 -> 30/360-30 days
			//per month  360 per year
			StringField<1> loan_Ff_Ind;       //Federal funds code
			//(CIF table)
			DoubleField loan_Dal_Int_Accr;       //Daily interest
			//accrual amount
			DoubleField loan_Tot_Int_Due;       //Total interest due
			//(fixed rate loans)
			StringField<2> loan_Int_Pay_Fr;   //Interest payment freq.
			// 1 - 98 -> number of
			//months between payments
			// 99 -> due at maturity
			StringField<2> loan_Int_Pay_Day;     //Interest payment day
			//(day of month)
			StringField<2> loan_Prin_Pay_Fr;  //Principal payment freq.
			// 1 - 98 -> number of
			//months between payments
			// 99 -> due at maturity
			StringField<2> loan_Prin_Pay_Day;    //Principal payment day
			//(day of month)
			StringField<1> loan_Branch;       //Branch code
			StringField<2> loan_Internal_Code; //Field for site-spec coding
			StringField<1> Fill1; //
			StringField<3> loan_Officer;       //Loan officer
			//(CIF acct man table)
			StringField<1> loan_Roll_Ind;      //Rollover indicator:
			// Y -> rollover loan
			// N -> no rollover
			StringField<1> loan_Rec_Ind;
			StringField<35> loan_Ref_Line1;     //2 lines of free text
			StringField<35> loan_Ref_Line2;       //for reference only
			StringField<1> loan_Fiduc_Deposit_Ind;   //= F IF Fiduciary drawn
			//	  against a Deposit
			//= D If it is a deposit
			//loan tied to a Fid.
			StringField<1> loan_Mat_Int_Settl_Ind;      //Flag to indicate if
			//interest maturity
			//instructions exist (Y/N)
			StringField<1> loan_Mat_Settl_Ind;      //Flag to indicate if
			//principal maturity
			//instructions exist (Y/N)
			WordField loan_Decimal_Places;  //Loan ccy decimal places
			StringField<2> loan_Cont_Count;   //Number of hedge contr.
			DoubleField loan_Var_Rate;   //Variable interest rate
			StringField<2> loan_Rate_Type;      //Interest rate type:
			// 1 -> fix rate loan
			// 2 - 99 -> var. rate type
			// as defined by floating
			// rate table
			StringField<1> loan_Perc_Ind;   //Percentage indicator :
			//P->LOAN.INT.RATE used
			//as % of LOAN.VAR.RATE
			//other- LOAN.INT.RATE
			//added to  LOAN.VAR.RATE
			StringField<1> loan_Repay_Type;  //Loan repayment type code:
			// 1 - Separate principal
			//  and interest
			// 2 - Single payment
			//	(mortgage type)
			StringField<6> loan_Libor_Exp_Date;    //Int. rate expiry date
			StringField<6> loan_Int_Paid_To_Date;    //Interest paid-to date
			DoubleField loan_Secured_Amount;   //Secured amount on loan
			DoubleField loan_Margin;      //Margin percent used
			//by Landerbank
			DoubleField loan_Unearned_Disc_Amt;    //Unearned discount amt
			//for discount loan
			DoubleField loan_Net_Proceed_Amt;  //Net proceeds (ie. issue
			// settlement amount)
			DoubleField loan_Neg_Int_Adj_Amt;    //Total amt of negative
			//interest adj.
			//stored as absolute value.
			//This must be added
			//to the amount paid when
			//using int paid to
			//calculate amount due.
			WordField loan_Roll_Inst_Ent;    //set to -1 if rollover
			//instruction have
			//been entered for rollover
			// coming due. This is
			//cleared on rollover date.
			StringField<6> loan_Roll_Issue_Date;    //Issue date of rollover
			//or issue date of
			//non-rollover loan.
			//This is used to check
			//the oldest allowable
			//back value date.
			DoubleField loan_Original_Amount;  //Original amount of loan
			//in source currency
			DoubleField loan_Original_Eq_Amount;  //Original amount of loan
			//in base currency
			DoubleField loan_Comm_Amount;       //Commission amount
			DoubleField loan_Daily_Dissagio_Amount;         //
			StringField<10> loan_Comm_Lim_Number;  //Commitment / Line number
			StringField<1> Fill2;
			StringField<2> loan_Profit_Ctr;       //Profit Center code
			//(CIF table)
			StringField<1> loan_Accr_Code;            //Accrual Code:
			// A -> regular accrual
			// C -> Discount Loan
			// D -> Call loan
			StringField<3> loan_Fed_Class;   //Federal Classification
			//code (CIF table)
			StringField<8> loan_Type;
			StringField<1> loan_Guar_Ind;  //Guarantor indicator (Y/N)
			StringField<1> loan_Status;       //Loan Status:
			// 1 -> Future
			// 2 -> Open
			// 3 -> Matured
			// 4 -> Interest Settled
			// 5 -> Principal Settled
			// 6 -> Matured and Settled
			// 7 -> Reversed
			StringField<1> loan_Iss_Cable_Sent_Ind;     //INDICATOR TO SHOW IF
			//CABLE SENT FOR
			// LOAN ISSUE Y = SENT
			// N = NOT SENT
			StringField<1> loan_Int_Cable_Sent_Ind;  // INTEREST CABLE INDICATOR
			// AS ABOVE
			// FLAG IS SET WHEN A
			// MESSAGE IS SENT TO
			// MT AND CLEARED WHEN
			// THE ACCTG IS DONE
			StringField<1> loan_Prin_Cable_Sent_Ind;       // PRINCIPALE CABLE
			// INDICATOR AS ABOVE
			DoubleField loan_Demand_Past_Due_Amt;       // FOR DEMAND LOANS
			// INTEREST ONLY
			StringField<6> loan_Demand_Prior_Due_Date;         //
			StringField<6> loan_Demand_Next_Due_Date;         //
			WordField loan_Mt_Doc_No;      // SEQUENCE NO FOR MT
			// INTERFACE
			WordField loan_Mt_Doc_Rev_No;      // SEQUENCE NO FOR MT
			// REVERSAL
			StringField<3> Fill3;         //
			StringField<3> loan_Comm_Currency;      //Commitment ccy from
			//clhskp
			DoubleField loan_Comm_Rate;       //Commitment to loan
			//conversion rate
			StringField<1> loan_Comm_Rate_Recp;      //'R' if comm rate is
			//reciprocal
			StringField<1> loan_Mail;  //'Y' to mail confirm/bills
			StringField<6> loan_Refi;       //Loan funding code
			//(not validated)
			StringField<6> loan_Security_Code;       //Loan security code
			//(not validated)
			StringField<6> loan_Rollover_Date;       //Loan rollover date
			StringField<1> loan_Prtcp_Ind;  //Flag to indicate if loan
			// is participated
			// Y => particapation
			// N => no participation
			StringField<1> loan_Prtcp_Recourse;   //Participation recourse
			//indicator
			//1= with recourse.
			//'Y' on the pymt. screen.
			// ignored by commitment
			// rebuild and ITC
			//2= without recourse.
			//'N' on pymt. screen
			// Increases Remaining
			// amount on commitment
			// when a part. Loan is
			// entered.  Decreases
			// Remaining amt. when
			// part. Loan payed off
			StringField<3> Fill4;           //
			StringField<1> loan_Auto_Prin_Pymt;      //Automatic principal
			//payments (during EOD)
			// Y = yes
			// N = manual settlement
			StringField<1> loan_Auto_Int_Pymt;       //Automatic Interest
			//payments (during EOD)
			// Y = yes
			// N = manual settlement
			StringField<6> loan_Auto_Prin_Pay_Date;   //Date of next automatic
			//principal pymt.
			StringField<6> loan_Auto_Int_Pay_Date;   //Date of next automatic
			//interest pymt.
			DoubleField loan_Dissagio_Amount;    // Amortized Commission
			// Amount
			StringField<1> loan_Dissagio_Ind;       // Y= YES N= NO
			StringField<1> loan_Fiduciary_Ind;   //TO show if the loan is
			//a Fiduciary loan
			StringField<13> loan_Prtcp_Cust_No;       //Customer number of
			//asset loan for sub
			//participations
			StringField<11> loan_Prtcp_No;    //Asset loan number for
			//sub participations
			//This is also used for
			//Deposit number
			StringField<6> loan_Begin_Date;   //Variant 2 Option (DSB)
			StringField<6> loan_End_Date;         //
			StringField<5> loan_Local_Sic;         //
			StringField<2> loan_Cost_Type;         //
			StringField<1> loan_Gross_Ind;         //
			StringField<1> Fill5;                         //
			StringField<4> loan_Cost_Center;         //
			DoubleField loan_Accr_Int_Rec;       //Accrued interest
			//recievable
			//rounded accrued amount
			//less interest paid
			//This is the amount of
			//interest due on the
			//loan as of today.
			//LOAN.NEG.INT.ADJ.AMT is
			// included.
			DoubleField loan_Tot_Int_Rec;  //Total interest received
			//not including
			//LOAN.NEG.INT.ADJ.AMT
			DoubleField loan_Ytd_Int_Rec;    //Year to date interest
			//received
			StringField<6> loan_Dat_Last_Accr;     //Date of last accrual
			//(accrual to-date)
			StringField<6> loan_Dat_Ls_Int_Pay;    //Date of last interest
			//payment
			StringField<2> Fill6;         //
			StringField<6> loan_Date_Set;       //Loan set up date
			//(date entered on system)
			StringField<6> loan_Payoff_Date;      //Date of loan payoff
			DoubleField loan_Acc_Todate;  //Accrued interest to date
			// (source currency)
			//LOAN.NEG.INT.ADJ.AMT is
			//included.
			DoubleField loan_Acc_Todate_Eqv;  //Accrued interest to date
			//equivalent (base)
			DoubleField loan_Tot_Int_Rec_Eqv;
			StringField<6> loan_Ls_Acct_Date;  //Date of last transaction
			//for loan
			DoubleField loan_Dissagio_Acc_Todate;     //Amortized Commission
			//Amount accrued todat
			StringField<24> Fill7;         //
			DoubleField loan_Earned_Disc_Amt;   //Earned discount amount
			DoubleField loan_Last_Auto_Int_Tax;     //Tax withheld on last
			//int payment if liab
			//LOAN.PREV.PERIOD.INT.INC
			//LOAN.CURR.PERIOD.INT.INC
			DoubleField loan_Last_Auto_Prin_Amt;     //Amount of last auto.
			//prin. pay to MT
			DoubleField loan_Last_Auto_Int_Amt;     //Amount of last auto.
			//interest pay to MT
			//not reduced by tax
			//withheld
			StringField<6> loan_Dat_Last_Rate_Chng;    //Date of last interest
			//rate change or last
			//libor rate expiration
			//date if rate didn't
			//change.
			StringField<6> loan_Dat_Last_Prnc_Chng;   //Date of last principal
			//change
			StringField<6> loan_Last_Auto_Prin_Date;       //Date of last auto.
			//principal payment
			//sent to MT
			StringField<6> loan_Last_Auto_Int_Date;       //Date of last auto.
			//interest payment to MT
			DoubleField loan_Curr_Period_Dollar_Days;  //Aggregate principal for
			//current month
			DoubleField loan_Prev_Period_Dollar_Days;  //Aggregate principal for
			//previous month
			DoubleField loan_Princ_Receivable;       //Past due principal
			//(according to notes)
			//Includes interest if
			//mortgage note
			DoubleField loan_Int_Receivable;       //Past due interest
			//(according to notes)
			//actually - total int
			//accrued-unrounded
			//not less interest paid.
			//LOAN.NEG.INT.ADJ.AMT is
			//included.
			DoubleField loan_Ytd_Dollar_Days;  //Aggregate principal for
			//year to date
			DoubleField loan_Curr_Per_Disc_Int_Ear;    //Aggregate interest on
			//loans for current month
			//not just discounted
			DoubleField loan_Int_Payoff_Amt;         //
			DoubleField loan_Prev_Per_Disc_Int_Ear;    //Aggregate interest on
			//loans for previous month
			//not just discounted
			DoubleField loan_Ytd_Disc_Int_Ear;    //Aggregate interest on
			//loans for year to date
			//not just discounted
			StringField<6> loan_Date_Last_Int_Due;     //Set to last interest
			//note due during billing
			StringField<89> Fill8;         //
			StringField<2> loan_Gl_br;       // Branch code
			StringField<6> loan_Reclass_Date;    //Date of the last TYPE
			//CHANGE for loan
			StringField<6> loan_Dem_Prin_Prior_Due_Date;       //For demand loans
			//principal
			StringField<6> loan_Dem_Prin_Next_Due_Date;         //
			DoubleField loan_High_Comm_Amount;    //Highest loan original
			//amount in comm cur
			StringField<6> Fill9;         //
			DoubleField loan_Security_Perc;         //
			WordField loan_Pos_Weight;         //
			StringField<6> loan_Actual_Rate_Chg_Date;      //Date of last actual
			//rate change. This date
			//will correspond to a
			//record in the hist file
			DoubleField loan_Tax_With_Perc;         //
			StringField<1> loan_Tax_With_Ind;         //
			StringField<1> loan_Assignment;         //
			StringField<1> loan_Cc2_Code;         //
			StringField<1> loan_Wikind; // WIK Loan indicator Y or N
			StringField<1> loan_Iblc_Std_Flag;  //The next 5 variable are
			// for lux
			StringField<6> loan_Iss_Principal_Iblc_Code;         //
			StringField<6> loan_Mat_Principal_Iblc_Code;         //
			StringField<6> loan_Iss_Sett_Iblc_Cod;         //
			StringField<6> loan_Mat_Sett_Iblc_Code;         //
			StringField<6> loan_Int_Iblc_Code;         //
			StringField<3> loan_Auth_Officer;       //Auth.officer (CIF
			//account manager table)
			WordField loan_Billing_Days;         //
			DoubleField loan_Collateral_Req_Minimum;         //
			DoubleField loan_Collateral_Value;         //
			StringField<6> loan_Collateral_Reval_Date;         //
			StringField<1> Fill10;       //MAP FOR CL  LOAN
		};
		Case
		{
			StringField<964> loan_Everything;
		};
		Case
		{
			StringField<412> Fill11;
			StringField<71> loan_Misc1;
		};
		Case
		{
			StringField<29> Fill12;
			StringField<339> loan_All;
		};
		Case
		{
			StringField<29> Fill13;
			Glno_rec loan_Gl;
			StringField<310> Fill14;
			Ityp_rec loan_Typ;
		};
	};
};
#pragma pack(pop)

#endif // CLMAP_CLLOAN650_REC_TYPES
