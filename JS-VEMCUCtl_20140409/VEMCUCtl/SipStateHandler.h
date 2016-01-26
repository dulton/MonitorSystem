#ifndef  _SIP_STATE_HANDLER_H_
#define _SIP_STATE_HANDLER_H_

#include "include\\IWLSipAPI.h"
#include "include\\IWLSipRegAPI.h"
#include "include\\IWLSipTrAPI.h"
#include "include\\IWLSipSdpAPI.h"
#include "include\\IWLSipCallAPI.h"
#include "include\\IWLPortAPI.h"
#include "SipUtil.h"

/***************************************����״̬������غ���***********************************/

//����UNDEFINED״̬������
BOOL SipCallStatusUndefinedHandler(unsigned int nCID,E_RtCallStateReason eReason,void* pAppData);

//����IDLE״̬������
BOOL SipCallStatusIdleHandler(unsigned int nCID,E_RtCallStateReason eReason,void* pAppData);

//����INVITING״̬������
BOOL SipCallStatusInvitingHandler(unsigned int	 nCID,E_RtCallStateReason eReason,void* pAppData);

//����OFFERING״̬������
BOOL SipCallStatusOfferingHandler(unsigned int nCID,E_RtCallStateReason eReason,void* pAppData);

//����PROCEEDING״̬������
BOOL SipCallStatusProceedingHandler(unsigned int nCID,E_RtCallStateReason eReason,void* pAppData);

//����RECV_CALL״̬������
BOOL SipCallStatusRecvCallHandler(unsigned int nCID,E_RtCallStateReason eReason,void* pAppData);

//����WAIT_TALKING״̬������
BOOL SipCallStatusWaitTalkHandler(unsigned int nCID,E_RtCallStateReason eReason,void* pAppData);

//����TALKING״̬������
BOOL SipCallStatusTalkingHandler(unsigned int nCID,E_RtCallStateReason eReason,void* pAppData);

//����TERMINATED״̬������
BOOL SipCallStatusTerminatedHandler(unsigned int nCID,E_RtCallStateReason eReason,void* pAppData);


/***************************************����״̬������غ���***********************************/

//����UNDEFINED״̬������
BOOL SipTransStatusUndefinedHandler(unsigned int nTID,E_RtTransactionStateReason eReason,void* pAppData);

//����IDLE״̬������
BOOL SipTransStatusIdleHandler(unsigned int nTID,E_RtTransactionStateReason eReason,void* pAppData);

//����OK״̬������
BOOL SipTransStatusOKHandler(unsigned int nTID,E_RtTransactionStateReason eReason,void* pAppData);

//����FAIL״̬������
BOOL SipTransStatusFailHandler(unsigned int nTID,E_RtTransactionStateReason eReason,void* pAppData);

//����PROCEEDING״̬������
BOOL SipTransStatusProceedingHandler(unsigned int nTID,E_RtTransactionStateReason eReason,void* pAppData);

//����RECV_REQ״̬������
BOOL SipTransStatusRecvReqHandler(unsigned int nTID,E_RtTransactionStateReason eReason,void* pAppData);

//����WAIT_USER_PROCESS״̬������
BOOL SipTransStatusWaitUserProcessHandler(unsigned int nTID,E_RtTransactionStateReason eReason,void* pAppData);

//����USER_ACK_ARRIVED״̬������
BOOL SipTransStatusUserAckArrivedHandler(unsigned int nTID,E_RtTransactionStateReason eReason,void* pAppData);

//����USER_ACK_DISCARD״̬������
BOOL SipTransStatusUserAckDiscardHandler(unsigned int nTID,E_RtTransactionStateReason eReason,void* pAppData);


#endif
