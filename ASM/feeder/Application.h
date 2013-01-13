#ifndef BULLTRADERS_APPLICATION_H
#define BULLTRADERS_APPLICATION_H

#include "quickfix/Application.h"
#include "quickfix/MessageCracker.h"
#include "quickfix/Values.h"
#include "quickfix/Mutex.h"

#include "quickfix/fix42/ExecutionReport.h"
#include "quickfix/fix42/MarketDataRequest.h"
#include "quickfix/fix42/MarketDataSnapshotFullRefresh.h"
#include "quickfix/fix42/QuoteRequest.h"
#include "quickfix/fix42/Quote.h"


#include <queue>

class Application :
      public FIX::Application,
      public FIX::MessageCracker
{
public:
  void run();


private:
  FIX::SenderCompID senderCompID;
  FIX::TargetCompID targetCompID;
  typedef std::vector<FIX::Message> Messages;
  Messages m_messages;


  void onCreate( const FIX::SessionID& ) {}
  void onLogon( const FIX::SessionID& sessionID );
  void onLogout( const FIX::SessionID& sessionID );
  void toAdmin( FIX::Message&, const FIX::SessionID& ) {}
  void toApp( FIX::Message&, const FIX::SessionID& )
  throw( FIX::DoNotSend );
  void fromAdmin( const FIX::Message&, const FIX::SessionID& )
  throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon ) {}
  void fromApp( const FIX::Message& message, const FIX::SessionID& sessionID )
  throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType );


  void onMessage( const FIX42::Quote&, const FIX::SessionID& );

  void queryQuoteRequest();


  void setHeader( FIX::Header& header );

};

#endif
