#ifndef ORDERMATCH_APPLICATION_H
#define ORDERMATCH_APPLICATION_H

#include "IDGenerator.h"
#include "OrderMatcher.h"
#include "Order.h"
#include <queue>
#include <iostream>

#include "../utils/AgentControl.h"

#include "quickfix/Application.h"
#include "quickfix/MessageCracker.h"
#include "quickfix/Values.h"
#include "quickfix/Utility.h"
#include "quickfix/Mutex.h"

#include "quickfix/fix42/NewOrderSingle.h"
#include "quickfix/fix42/OrderCancelRequest.h"
#include "quickfix/fix42/MarketDataSnapshotFullRefresh.h"
#include "quickfix/fix42/QuoteRequest.h"
#include "quickfix/fix42/Quote.h"

#include "quickfix/fix42/MarketDataRequest.h"
#include "quickfix/fix43/MarketDataRequest.h"
#include "quickfix/fix44/NewOrderSingle.h"

class Application
      : public FIX::Application,
        public FIX::MessageCracker
{
  // Application overloads
  void onCreate( const FIX::SessionID& ) {}
  void onLogon( const FIX::SessionID& sessionID );
  void onLogout( const FIX::SessionID& sessionID );
  void toAdmin( FIX::Message&, const FIX::SessionID& ) {}
  void toApp( FIX::Message&, const FIX::SessionID& )
  throw( FIX::DoNotSend ) {}
  void fromAdmin( const FIX::Message&, const FIX::SessionID& )
  throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon ) {}
  void fromApp( const FIX::Message& message, const FIX::SessionID& sessionID )
  throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType );

  // MessageCracker overloads
  void onMessage( const FIX42::NewOrderSingle&, const FIX::SessionID& );
  void onMessage( const FIX44::NewOrderSingle&, const FIX::SessionID& );
  void onMessage( const FIX42::OrderCancelRequest&, const FIX::SessionID& );
  void onMessage( const FIX42::MarketDataRequest&, const FIX::SessionID& );
  void onMessage( const FIX42::QuoteRequest&, const FIX::SessionID& );
  void sendQuoteMessage( FIX::Symbol symbol,FIX::SenderCompID targetCompID);
  void onMessage( const FIX43::MarketDataRequest&, const FIX::SessionID& );

  // Order functionality
  void processOrder( const Order& );
  void processCancel( const std::string& id, const std::string& symbol, Order::Side );

  void updateOrder( const Order&, char status );
  void rejectOrder( const Order& order )
  { updateOrder( order, FIX::OrdStatus_REJECTED ); }
  void acceptOrder( const Order& order )
  { updateOrder( order, FIX::OrdStatus_NEW ); }
  void fillOrder( const Order& order )
  {
    updateOrder( order,
                 order.isFilled() ? FIX::OrdStatus_FILLED
                 : FIX::OrdStatus_PARTIALLY_FILLED );
  }
  void cancelOrder( const Order& order )
  { updateOrder( order, FIX::OrdStatus_CANCELED ); }

  void rejectOrder( const FIX::SenderCompID&, const FIX::TargetCompID&,
                    const FIX::ClOrdID& clOrdID, const FIX::Symbol& symbol,
                    const FIX::Side& side, const std::string& message );




  // Type conversions
  Order::Side convert( const FIX::Side& );
  Order::Type convert( const FIX::OrdType& );
  FIX::Side convert( Order::Side );
  FIX::OrdType convert( Order::Type );

  OrderMatcher m_orderMatcher;
  IDGenerator m_generator;
  FIX::SenderCompID _senderCompID;

  AgentControl agentControl;

public:
  const OrderMatcher& orderMatcher() { return m_orderMatcher; }
  void setAgentControl(AgentControl agentControl);
};

#endif
