#include "quickfix/Application.h"
#include "quickfix/MessageCracker.h"
#include "quickfix/Values.h"
#include "quickfix/Mutex.h"
#include "IDGenerator.h"

#include "quickfix/fix42/NewOrderSingle.h"
#include "quickfix/fix42/ExecutionReport.h"
#include "quickfix/fix42/OrderCancelRequest.h"
#include "quickfix/fix42/OrderCancelReject.h"
#include "quickfix/fix42/OrderCancelReplaceRequest.h"
#include "quickfix/fix42/MarketDataRequest.h"
#include "quickfix/fix42/MarketDataSnapshotFullRefresh.h"
#include "quickfix/fix42/QuoteRequest.h"
#include "quickfix/fix42/Quote.h"
#include "quickfix/fix42/Message.h"
#include "Strategy.h"
#include "SimpleOrder.h"

class Application :
      public FIX::Application,
      public FIX::MessageCracker
{
public:
  void run();
  void setStrategy( Strategy& strategy );


private:
  Strategy strategy;
  FIX::SenderCompID senderCompID;
  FIX::TargetCompID targetCompID;

  bool getConfirmationTrade;
  bool getConfirmationExecutionTrade;
  bool getConfirmationPartialExecutionTrade;
  bool getConfirmationCanceledTrade;

  IDGenerator m_generator;

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

  void onMessage( const FIX42::ExecutionReport&, const FIX::SessionID& );
  void onMessage( const FIX42::OrderCancelReject&, const FIX::SessionID& );
  void onMessage( const FIX42::MarketDataSnapshotFullRefresh&, const FIX::SessionID& );
  void onMessage( const FIX42::Quote&, const FIX::SessionID& );

  void resetFlags();

  void sendOrder(SimpleOrder order);
  void cancelOrder(SimpleOrder order);

  void waitGetCancelConfirmationResponse();


  void queryMarketDataRequest();


  void setHeader( FIX::Header& header );


};

