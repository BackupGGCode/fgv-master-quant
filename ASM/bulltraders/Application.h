#ifndef BULLTRADERS_APPLICATION_H
#define BULLTRADERS_APPLICATION_H

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


#include <queue>

class Application :
      public FIX::Application,
      public FIX::MessageCracker
{
public:
  void run();
  void runBOT();

private:
  FIX::SenderCompID senderCompID;
  FIX::TargetCompID targetCompID;
  typedef std::vector<FIX::Message> Messages;
  Messages m_messages;
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

  void queryEnterOrder();
  void queryCancelOrder();
  void queryReplaceOrder();
  void queryMarketDataRequest();
  void queryQuoteRequest();

  FIX42::NewOrderSingle queryNewOrderSingle42();
  void sendOrder(FIX::Symbol symbol, FIX::Side side, FIX::OrderQty orderQty, FIX::Price price);
  void cancelOrder( FIX::Symbol symbol, FIX::Side side,	FIX::OrderQty orderQty, FIX::Price price);

  FIX42::OrderCancelRequest queryOrderCancelRequest42();
  FIX42::OrderCancelReplaceRequest queryCancelReplaceRequest42();

  void setHeader( FIX::Header& header );
  char queryAction();
  char canGo();
  bool queryConfirm( const std::string& query );

  FIX::TargetSubID queryTargetSubID();
  FIX::ClOrdID queryClOrdID();
  FIX::OrigClOrdID queryOrigClOrdID();
  FIX::Symbol querySymbol();
  FIX::Side querySide();
  FIX::OrderQty queryOrderQty();
  FIX::OrdType queryOrdType();
  FIX::Price queryPrice();
  FIX::StopPx queryStopPx();
  FIX::TimeInForce queryTimeInForce();
};

#endif
