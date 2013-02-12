
#ifdef _MSC_VER
#pragma warning( disable : 4503 4355 4786 )
#else
#include "config.h"
#endif

#include "Application.h"
#include "../../src/C++/Session.h"

#include "quickfix/fix42/ExecutionReport.h"
#include "quickfix/fix42/MarketDataRequest.h"
#include "quickfix/fix42/MarketDataSnapshotFullRefresh.h"

void Application::onLogon( const FIX::SessionID& sessionID ) {
	  this->_senderCompID = sessionID.getSenderCompID();
}

void Application::onLogout( const FIX::SessionID& sessionID ) {}

void Application::fromApp( const FIX::Message& message,
                           const FIX::SessionID& sessionID )
throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType )
{
  crack( message, sessionID );
}

void Application::onMessage( const FIX42::NewOrderSingle& message, const FIX::SessionID& )
{


  FIX::SenderCompID senderCompID;
  FIX::TargetCompID targetCompID;
  FIX::ClOrdID clOrdID;
  FIX::Symbol symbol;
  FIX::Side side;
  FIX::OrdType ordType;
  FIX::Price price;
  FIX::OrderQty orderQty;
  FIX::TimeInForce timeInForce( FIX::TimeInForce_DAY );

  message.getHeader().get( senderCompID );
  message.getHeader().get( targetCompID );
  message.get( clOrdID );
  message.get( symbol );
  message.get( side );
  message.get( ordType );
  if ( ordType == FIX::OrdType_LIMIT )
    message.get( price );
  message.get( orderQty );
  if ( message.isSetField( timeInForce ) )
    message.get( timeInForce );

  try
  {
    if ( timeInForce != FIX::TimeInForce_DAY )
      throw std::logic_error( "Unsupported TIF, use Day" );

    Order order( clOrdID, symbol, senderCompID, targetCompID,
                 convert( side ), convert( ordType ),
                 price, (long)orderQty );

    processOrder( order );
  }
  catch ( std::exception & e )
  {
    rejectOrder( senderCompID, targetCompID, clOrdID, symbol, side, e.what() );
  }
}

void Application::onMessage( const FIX44::NewOrderSingle& message, const FIX::SessionID& )
{
  FIX::SenderCompID senderCompID;
  FIX::TargetCompID targetCompID;
  FIX::ClOrdID clOrdID;
  FIX::Symbol symbol;
  FIX::Side side;
  FIX::OrdType ordType;
  FIX::Price price;
  FIX::OrderQty orderQty;
  FIX::TimeInForce timeInForce( FIX::TimeInForce_DAY );

  message.getHeader().get( senderCompID );
  message.getHeader().get( targetCompID );
  message.get( clOrdID );
  message.get( symbol );
  message.get( side );
  message.get( ordType );
  if ( ordType == FIX::OrdType_LIMIT )
    message.get( price );
  message.get( orderQty );
  if ( message.isSetField( timeInForce ) )
    message.get( timeInForce );

  try
  {
    if ( timeInForce != FIX::TimeInForce_DAY )
      throw std::logic_error( "Unsupported TIF, use Day" );

    Order order( clOrdID, symbol, senderCompID, targetCompID,
                 convert( side ), convert( ordType ),
                 price, (long)orderQty );

    processOrder( order );
  }
  catch ( std::exception & e )
  {
    rejectOrder( senderCompID, targetCompID, clOrdID, symbol, side, e.what() );
  }
}


void Application::onMessage( const FIX42::OrderCancelRequest& message, const FIX::SessionID& )
{
  FIX::OrigClOrdID origClOrdID;
  FIX::Symbol symbol;
  FIX::Side side;

  message.get( origClOrdID );
  message.get( symbol );
  message.get( side );

  try
  {
    processCancel( origClOrdID, symbol, convert( side ) );
  }
  catch ( std::exception& ) {}}


/*
void Application::onMessage( const FIX42::MarketDataRequest& message, const FIX::SessionID& )
{

  FIX::MDReqID mdReqID;
  FIX::SubscriptionRequestType subscriptionRequestType;
  FIX::MarketDepth marketDepth;
  FIX::NoRelatedSym noRelatedSym;
  FIX42::MarketDataRequest::NoRelatedSym noRelatedSymGroup;

  message.get( mdReqID );
  message.get( subscriptionRequestType );
  if ( subscriptionRequestType != FIX::SubscriptionRequestType_SNAPSHOT )
    throw( FIX::IncorrectTagValue( subscriptionRequestType.getField() ) );
  message.get( marketDepth );
  message.get( noRelatedSym );

  for ( int i = 1; i <= noRelatedSym; ++i )
  {
    FIX::Symbol symbol;
    message.getGroup( i, noRelatedSymGroup );
    noRelatedSymGroup.get( symbol );
  }

}
*/


void Application::onMessage( const FIX42::MarketDataRequest& message, const FIX::SessionID& )
{

  //std::cout  << "[MarketDataSnapshotFullRefresh]"<< std::endl;

  FIX::MDReqID mdReqID;
  FIX::SubscriptionRequestType subscriptionRequestType;
  FIX::MarketDepth marketDepth;
  FIX::NoRelatedSym noRelatedSym;
  FIX42::MarketDataRequest::NoRelatedSym noRelatedSymGroup;

  FIX::SenderCompID senderCompID;
  FIX::TargetCompID targetCompID;

  message.getHeader().get( senderCompID );
  message.getHeader().get( targetCompID );

  message.get( mdReqID );

  message.get( subscriptionRequestType );
  message.get( noRelatedSym );
  message.get( marketDepth );


  if ( noRelatedSym == 1){
	  FIX42::MarketDataSnapshotFullRefresh resp;

	  resp.setField(mdReqID);

	  FIX::Symbol symbol;
	  message.getGroup(1, noRelatedSymGroup );
	  noRelatedSymGroup.get( symbol );
	  resp.setField(symbol);

	  std::vector<Order> mdOrderBuy = m_orderMatcher.getMDOrderBook(symbol, Order::buy);
	  //std::cout  << "mdOrderBuy.size="<< mdOrderBuy.size()<<std::endl;
	  for (int i=0; (i < (int)mdOrderBuy.size()  && i < marketDepth); i++){
		  FIX42::MarketDataSnapshotFullRefresh::NoMDEntries group;
		  FIX::MDEntryType MDEntryType(FIX::MDEntryType_OFFER);
		  FIX::MDEntryPx MDEntryPx(mdOrderBuy[i].getPrice());
		  FIX::MDEntrySize MDEntrySize(mdOrderBuy[i].getOpenQuantity());
		  FIX::MDEntrySeller MDEntrySeller(mdOrderBuy[i].getOwner());
		  group.set(MDEntryType);
		  group.set(MDEntryPx);
		  group.set(MDEntrySize);
		  group.set(MDEntrySeller);
		  resp.addGroup(group);
	  }
	  std::vector<Order> mdOrderSell = m_orderMatcher.getMDOrderBook(symbol, Order::sell);
	  //std::cout  << "mdOrderSell.size="<< mdOrderSell.size()<<std::endl;
	  for (int i=0; (i < (int)mdOrderSell.size() && i < marketDepth); i++){
		  FIX42::MarketDataSnapshotFullRefresh::NoMDEntries group;
		  FIX::MDEntryType MDEntryType(FIX::MDEntryType_BID);
		  FIX::MDEntryPx MDEntryPx(mdOrderSell[i].getPrice());
		  FIX::MDEntrySize MDEntrySize(mdOrderSell[i].getOpenQuantity());
		  FIX::MDEntryBuyer MDEntryBuyer(mdOrderSell[i].getOwner());
		  group.set(MDEntryType);
		  group.set(MDEntryPx);
		  group.set(MDEntrySize);
		  resp.addGroup(group);
	  }
	  FIX::Session::sendToTarget( resp,targetCompID ,senderCompID  );

  }else{

	  for ( int i = 1; i <= noRelatedSym; ++i ){
	    FIX::Symbol symbol;
	    message.getGroup( i, noRelatedSymGroup );
	    noRelatedSymGroup.get( symbol );

	  }

  }


}

void Application::onMessage( const FIX42::QuoteRequest& message, const FIX::SessionID& )
{
	  FIX::SenderCompID targetCompID;
	  message.getHeader().get( targetCompID );
	  FIX::Symbol symbol;
	  FIX42::QuoteRequest::NoRelatedSym noRelatedSymGroup;
	  message.getGroup(1, noRelatedSymGroup );
	  noRelatedSymGroup.get( symbol );

	  this->sendQuoteMessage(symbol,targetCompID );
}

void Application::sendQuoteMessage(FIX::Symbol symbol,FIX::SenderCompID targetCompID){
	  FIX42::Quote resp;

	  if(m_orderMatcher.isThereLastMarketData(symbol)){ // tem pelo menos 1 bid ou 1 ask
		  	FIX::QuoteID quoteID( m_generator.genQuoteID());

			FIX::BidPx bidPx(m_orderMatcher.getLastMarketData(symbol,Order::buy).getPrice());
			FIX::BidSize bidSize(bidPx > 0.0 ? m_orderMatcher.getLastMarketData(symbol,Order::buy).getOpenQuantity(): 0);


			FIX::OfferPx offerPx(m_orderMatcher.getLastMarketData(symbol,Order::sell).getPrice());
			FIX::OfferSize offerSize(offerPx > 0.0 ? m_orderMatcher.getLastMarketData(symbol,Order::sell).getOpenQuantity(): 0);

		  resp.setField(quoteID);
		  resp.setField(symbol);
		  resp.setField(bidPx);
		  resp.setField(bidSize);
		  resp.setField(offerPx);
		  resp.setField(offerSize);

		  FIX::Session::sendToTarget( resp,this->_senderCompID ,targetCompID);
	  }
	  else{

		  FIX::QuoteID quoteID( m_generator.genQuoteID());
		  FIX::BidPx bidPx(0);
		  FIX::OfferPx offerPx(0);
		  FIX::BidSize bidSize(0);
		  FIX::OfferSize offerSize(0);

		  resp.setField(quoteID);
		  resp.setField(symbol);
		  resp.setField(bidPx);
		  resp.setField(bidSize);
		  resp.setField(offerPx);
		  resp.setField(offerSize);
		  FIX::Session::sendToTarget( resp,this->_senderCompID ,targetCompID);
	  }

}


void Application::onMessage( const FIX43::MarketDataRequest& message, const FIX::SessionID& )
{
    //std::cout << message.toXML() << std::endl;
}

void Application::updateOrder( const Order& order, char status )
{
  FIX::TargetCompID targetCompID( order.getOwner() );
  FIX::SenderCompID senderCompID( order.getTarget() );

  FIX42::ExecutionReport fixOrder
  ( FIX::OrderID ( order.getClientID() ),
    FIX::ExecID ( m_generator.genExecutionID() ),
    FIX::ExecTransType ( FIX::ExecTransType_NEW ),
    FIX::ExecType ( status ),
    FIX::OrdStatus ( status ),
    FIX::Symbol ( order.getSymbol() ),
    FIX::Side ( convert( order.getSide() ) ),
    FIX::LeavesQty ( order.getOpenQuantity() ),
    FIX::CumQty ( order.getExecutedQuantity() ),
    FIX::AvgPx ( order.getAvgExecutedPrice() ) );

  fixOrder.set( FIX::ClOrdID( order.getClientID() ) );
  fixOrder.set( FIX::OrderQty( order.getQuantity() ) );

  if ( status == FIX::OrdStatus_FILLED ||
       status == FIX::OrdStatus_PARTIALLY_FILLED )
  {
    fixOrder.set( FIX::LastShares( order.getLastExecutedQuantity() ) );
    fixOrder.set( FIX::LastPx( order.getLastExecutedPrice() ) );
  }

  try
  {
    FIX::Session::sendToTarget( fixOrder, senderCompID, targetCompID );
    //this->sendQuoteMessage(order.getSymbol(), FIX::SenderCompID("FEEDER"));
  }
  catch ( FIX::SessionNotFound& ) {}}

void Application::rejectOrder
( const FIX::SenderCompID& sender, const FIX::TargetCompID& target,
  const FIX::ClOrdID& clOrdID, const FIX::Symbol& symbol,
  const FIX::Side& side, const std::string& message )
{
  FIX::TargetCompID targetCompID( sender.getValue() );
  FIX::SenderCompID senderCompID( target.getValue() );

  FIX42::ExecutionReport fixOrder
  ( FIX::OrderID ( clOrdID.getValue() ),
    FIX::ExecID ( m_generator.genExecutionID() ),
    FIX::ExecTransType ( FIX::ExecTransType_NEW ),
    FIX::ExecType ( FIX::ExecType_REJECTED ),
    FIX::OrdStatus ( FIX::ExecType_REJECTED ),
    symbol, side, FIX::LeavesQty( 0 ), FIX::CumQty( 0 ), FIX::AvgPx( 0 ) );

  fixOrder.set( clOrdID );
  fixOrder.set( FIX::Text( message ) );

  try
  {
    FIX::Session::sendToTarget( fixOrder, senderCompID, targetCompID );
  }
  catch ( FIX::SessionNotFound& ) {}}

void Application::processOrder( const Order& order )
{
  if ( m_orderMatcher.insert( order ) )
  {
    acceptOrder( order );

    std::queue < Order > orders;
    m_orderMatcher.match( order.getSymbol(), orders );

    while ( orders.size() )
    {
      fillOrder( orders.front() );
      orders.pop();
    }
  }
  else
    rejectOrder( order );
}

void Application::processCancel( const std::string& id,
                                 const std::string& symbol, Order::Side side )
{
  Order & order = m_orderMatcher.find( symbol, side, id );
  order.cancel();
  cancelOrder( order );
  m_orderMatcher.erase( order );
}

Order::Side Application::convert( const FIX::Side& side )
{
  switch ( side )
  {
    case FIX::Side_BUY: return Order::buy;
    case FIX::Side_SELL: return Order::sell;
    default: throw std::logic_error( "Unsupported Side, use buy or sell" );
  }
}

Order::Type Application::convert( const FIX::OrdType& ordType )
{
  switch ( ordType )
  {
    case FIX::OrdType_LIMIT: return Order::limit;
    default: throw std::logic_error( "Unsupported Order Type, use limit" );
  }
}

FIX::Side Application::convert( Order::Side side )
{
  switch ( side )
  {
    case Order::buy: return FIX::Side( FIX::Side_BUY );
    case Order::sell: return FIX::Side( FIX::Side_SELL );
    default: throw std::logic_error( "Unsupported Side, use buy or sell" );
  }
}

FIX::OrdType Application::convert( Order::Type type )
{
  switch ( type )
  {
    case Order::limit: return FIX::OrdType( FIX::OrdType_LIMIT );
    default: throw std::logic_error( "Unsupported Order Type, use limit" );
  }
}
