#include "config.h"
#include "Application.h"
#include "quickfix/Session.h"
#include <iostream>

void Application::onLogon( const FIX::SessionID& sessionID )
{
  std::cout << std::endl << "Logon - " << sessionID << std::endl;
  this->senderCompID = sessionID.getSenderCompID();
  this->targetCompID = sessionID.getTargetCompID();

}

void Application::onLogout( const FIX::SessionID& sessionID )
{
  std::cout << std::endl << "Logout - " << sessionID << std::endl;
}

void Application::fromApp( const FIX::Message& message, const FIX::SessionID& sessionID )
throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType )
{
  crack( message, sessionID );
  std::cout << std::endl << "IN: " << message.toXML() << std::endl;

}

void Application::toApp( FIX::Message& message, const FIX::SessionID& sessionID )
throw( FIX::DoNotSend )
{
  try
  {
    FIX::PossDupFlag possDupFlag;
    message.getHeader().getField( possDupFlag );
    if ( possDupFlag ) throw FIX::DoNotSend();
  }
  catch ( FIX::FieldNotFound& ) {}

  std::cout << std::endl
  << "OUT: " << message.toXML()  << std::endl;
}

void Application::onMessage
( const FIX42::ExecutionReport&, const FIX::SessionID& ) {}
void Application::onMessage
( const FIX42::OrderCancelReject&, const FIX::SessionID& ) {}
void Application::onMessage
( const FIX42::MarketDataSnapshotFullRefresh&, const FIX::SessionID& ) {}

/*
void Application::run()
{
  while ( true )
  {
    try
    {
      char action = queryAction();

      if ( action == '1' )
        queryEnterOrder();
      else if ( action == '2' )
        queryCancelOrder();
      else if ( action == '3' )
        queryReplaceOrder();
      else if ( action == '4' )
        queryMarketDataRequest();
      else if ( action == '5' )
        break;
    }
    catch ( std::exception & e )
    {
      std::cout << "Message Not Sent: " << e.what();
    }
  }
}
*/
void Application::runBOT()
{
  while ( true )
  {
    try
    {
      char action = canGo();
      FIX::Symbol symbol("IBM");

      switch(action){
      case 's':
    	  std::cout << "Sending order ... " << std::endl;
    	  this->sendOrder(symbol, FIX::Side_BUY, 314, 125.9);
    	  break;
      case 'c':
    	  std::cout << "Canceling order ... " << std::endl;
    	  this->cancelOrder(symbol, FIX::Side_BUY, 314, 125.9);
    	  break;
      default:
    	  std::cout << "Getting market data... " << std::endl;
    	  queryMarketDataRequest();
    	  break;
      }
    }
    catch ( std::exception & e )
    {
      std::cout << "Problem " << e.what();
    }
  }
}

char Application::canGo()
{
  char value;
  std::cout << std::endl
  << "(s)end Order" << std::endl
  << "(c)ancel Order" << std::endl
  << "Action: ";
  std::cin >> value;
  return value;
}

void Application::sendOrder(FIX::Symbol symbol, FIX::Side side,
							FIX::OrderQty orderQty, FIX::Price price){

  FIX::ClOrdID clOrdID;
  clOrdID = m_generator.genOrderID();
  FIX42::NewOrderSingle newOrderSingle;
  newOrderSingle.set( clOrdID );
  newOrderSingle.set(FIX::HandlInst( '1' ));
  newOrderSingle.set( symbol );
  newOrderSingle.set( side );
  newOrderSingle.set(FIX::TransactTime());
  newOrderSingle.set( FIX::OrdType( FIX::OrdType_LIMIT ) );
  newOrderSingle.set( orderQty );
  newOrderSingle.set( FIX::TimeInForce( FIX::TimeInForce_DAY ) );
  newOrderSingle.set( price );
  setHeader( newOrderSingle.getHeader() );
  m_messages.push_back(newOrderSingle);
  FIX::Session::sendToTarget( newOrderSingle );
}

void Application::cancelOrder(FIX::Symbol symbol, FIX::Side side,
													FIX::OrderQty orderQty, FIX::Price price){

  FIX42::OrderCancelRequest orderCancelRequest;
  FIX::ClOrdID clOrdID;
  clOrdID = m_generator.genOrderID();
  orderCancelRequest.set(FIX::ClOrdID( clOrdID ));
  //orderCancelRequest.set(FIX::OrigClOrdID( origClOrdID ));
  orderCancelRequest.set( symbol );
  orderCancelRequest.set( side );
  orderCancelRequest.set(FIX::TransactTime());
  orderCancelRequest.set( orderQty );
  setHeader( orderCancelRequest.getHeader() );


  for (int i=0; i < m_messages.size(); i++){
	  FIX::Symbol _symbol;
  	  FIX::Side _side;
  	  FIX::OrderQty _orderQty;
  	  FIX::Price _price;
  	  FIX::ClOrdID _origClOrdID;
  	  m_messages[i].getField(_symbol);
  	  m_messages[i].getField(_side);
  	  m_messages[i].getField(_orderQty);
  	  m_messages[i].getField(_price);
  	  m_messages[i].getField(_origClOrdID);

    if ( (_symbol==symbol)&&(_side==side)&&(_orderQty==orderQty)&&(_price==price))
    {
      orderCancelRequest.set(FIX::OrigClOrdID (_origClOrdID));
      m_messages.erase(m_messages.begin()+i);
      FIX::Session::sendToTarget( orderCancelRequest );
    }
  }

}

void Application::queryEnterOrder()
{
  std::cout << "\nNewOrderSingle\n";
  FIX::Message order;
  order = queryNewOrderSingle42();

  if ( queryConfirm( "Send order" ) )
    FIX::Session::sendToTarget( order );
}

void Application::queryCancelOrder()
{
  std::cout << "\nOrderCancelRequest\n";
  FIX::Message cancel;
  cancel = queryOrderCancelRequest42();

  if ( queryConfirm( "Send cancel" ) )
    FIX::Session::sendToTarget( cancel );
}

void Application::queryReplaceOrder()
{
  std::cout << "\nCancelReplaceRequest\n";
  FIX::Message replace;
  replace = queryCancelReplaceRequest42();

  if ( queryConfirm( "Send replace" ) )
    FIX::Session::sendToTarget( replace );
}

void Application::queryMarketDataRequest()
{
  std::cout << "\nMarketDataRequest\n";
  FIX::Message md;
  md = queryMarketDataRequest42();

  FIX::Session::sendToTarget( md );
}


FIX42::NewOrderSingle Application::queryNewOrderSingle42()
{
  FIX::OrdType ordType;

  FIX42::NewOrderSingle newOrderSingle(
    queryClOrdID(), FIX::HandlInst( '1' ), querySymbol(), querySide(),
    FIX::TransactTime(), ordType = queryOrdType() );

  newOrderSingle.set( queryOrderQty() );
  newOrderSingle.set( queryTimeInForce() );
  if ( ordType == FIX::OrdType_LIMIT || ordType == FIX::OrdType_STOP_LIMIT )
    newOrderSingle.set( queryPrice() );
  if ( ordType == FIX::OrdType_STOP || ordType == FIX::OrdType_STOP_LIMIT )
    newOrderSingle.set( queryStopPx() );

  setHeader( newOrderSingle.getHeader() );
  return newOrderSingle;
}

FIX42::OrderCancelRequest Application::queryOrderCancelRequest42()
{
  FIX42::OrderCancelRequest orderCancelRequest( queryOrigClOrdID(),
      queryClOrdID(), querySymbol(), querySide(), FIX::TransactTime() );

  orderCancelRequest.set( queryOrderQty() );
  setHeader( orderCancelRequest.getHeader() );
  return orderCancelRequest;
}


FIX42::OrderCancelReplaceRequest Application::queryCancelReplaceRequest42()
{
  FIX42::OrderCancelReplaceRequest cancelReplaceRequest(
    queryOrigClOrdID(), queryClOrdID(), FIX::HandlInst( '1' ),
    querySymbol(), querySide(), FIX::TransactTime(), queryOrdType() );

  if ( queryConfirm( "New price" ) )
    cancelReplaceRequest.set( queryPrice() );
  if ( queryConfirm( "New quantity" ) )
    cancelReplaceRequest.set( queryOrderQty() );

  setHeader( cancelReplaceRequest.getHeader() );
  return cancelReplaceRequest;
}


FIX42::MarketDataRequest Application::queryMarketDataRequest42()
{

  FIX::MDReqID mdReqID( "MARKETDATAID" );
  FIX::SubscriptionRequestType subType( '1' );
  FIX::MarketDepth marketDepth( 2 );
  FIX::MDUpdateType mDUpdateType(1);
  FIX::AggregatedBook aggregatedBook(true);
  //FIX::NoMDEntryTypes

  FIX42::MarketDataRequest::NoMDEntryTypes marketDataEntryGroup;
  FIX::MDEntryType mdEntryType1( FIX::MDEntryType_BID );
  FIX::MDEntryType mdEntryType2( FIX::MDEntryType_OFFER);
  marketDataEntryGroup.set( mdEntryType1 );
  marketDataEntryGroup.set( mdEntryType2 );


  FIX42::MarketDataRequest::NoRelatedSym symbolGroup;
  FIX::Symbol symbol( "IBM" );
  symbolGroup.set( symbol );

  FIX42::MarketDataRequest message( mdReqID, subType, marketDepth );
  message.addGroup( marketDataEntryGroup );
  message.addGroup( symbolGroup );
  message.set(mDUpdateType);
  message.set(aggregatedBook);

  setHeader( message.getHeader() );

  //std::cout << message.toXML() << std::endl;
  //std::cout << message.toString() << std::endl;

  FIX::Session::sendToTarget( message );

  return message;
}

void Application::setHeader( FIX::Header& header )
{
  header.setField(this->senderCompID);
  header.setField( this->targetCompID );

  //if ( queryConfirm( "Use a TargetSubID" ) )
  //  header.setField( queryTargetSubID() );
}

char Application::queryAction()
{
  char value;
  std::cout << std::endl
  << "1) Enter Order" << std::endl
  << "2) Cancel Order" << std::endl
  << "3) Replace Order" << std::endl
  << "4) Market data test" << std::endl
  << "5) Quit" << std::endl
  << "Action: ";
  std::cin >> value;
  switch ( value )
  {
    case '1': case '2': case '3': case '4': case '5': break;
    default: throw std::exception();
  }
  return value;
}


bool Application::queryConfirm( const std::string& query )
{
  std::string value;
  std::cout << std::endl << query << "?: ";
  std::cin >> value;
  return toupper( *value.c_str() ) == 'Y';
}

FIX::TargetSubID Application::queryTargetSubID()
{
  std::string value;
  //std::cout << std::endl << "TargetSubID: ";
  //std::cin >> value;
  value="2";
  std::cout << std::endl << "TargetSubID: " << value;
  return FIX::TargetSubID( value );
}

FIX::ClOrdID Application::queryClOrdID()
{
  std::string value;
  std::cout << std::endl << "ClOrdID: ";
  std::cin >> value;
  return FIX::ClOrdID( value );
}

FIX::OrigClOrdID Application::queryOrigClOrdID()
{
  std::string value;
  std::cout << std::endl << "OrigClOrdID: ";
  std::cin >> value;
  return FIX::OrigClOrdID( value );
}

FIX::Symbol Application::querySymbol()
{
  std::string value;
  std::cout << std::endl << "Symbol: ";
  std::cin >> value;
  return FIX::Symbol( value );
}

FIX::Side Application::querySide()
{
  char value;
  std::cout << std::endl
  << "1) Buy" << std::endl
  << "2) Sell" << std::endl
  << "3) Sell Short" << std::endl
  << "4) Sell Short Exempt" << std::endl
  << "5) Cross" << std::endl
  << "6) Cross Short" << std::endl
  << "7) Cross Short Exempt" << std::endl
  << "Side: ";

  std::cin >> value;
  switch ( value )
  {
    case '1': return FIX::Side( FIX::Side_BUY );
    case '2': return FIX::Side( FIX::Side_SELL );
    case '3': return FIX::Side( FIX::Side_SELL_SHORT );
    case '4': return FIX::Side( FIX::Side_SELL_SHORT_EXEMPT );
    case '5': return FIX::Side( FIX::Side_CROSS );
    case '6': return FIX::Side( FIX::Side_CROSS_SHORT );
    case '7': return FIX::Side( 'A' );
    default: throw std::exception();
  }
}

FIX::OrderQty Application::queryOrderQty()
{
  long value;
  std::cout << std::endl << "OrderQty: ";
  std::cin >> value;
  return FIX::OrderQty( value );
}

FIX::OrdType Application::queryOrdType()
{
  char value;
  std::cout << std::endl
  << "1) Market" << std::endl
  << "2) Limit" << std::endl
  << "3) Stop" << std::endl
  << "4) Stop Limit" << std::endl
  << "OrdType: ";

  std::cin >> value;
  switch ( value )
  {
    case '1': return FIX::OrdType( FIX::OrdType_MARKET );
    case '2': return FIX::OrdType( FIX::OrdType_LIMIT );
    case '3': return FIX::OrdType( FIX::OrdType_STOP );
    case '4': return FIX::OrdType( FIX::OrdType_STOP_LIMIT );
    default: throw std::exception();
  }
}

FIX::Price Application::queryPrice()
{
  double value;
  std::cout << std::endl << "Price: ";
  std::cin >> value;
  return FIX::Price( value );
}

FIX::StopPx Application::queryStopPx()
{
  double value;
  std::cout << std::endl << "StopPx: ";
  std::cin >> value;
  return FIX::StopPx( value );
}

FIX::TimeInForce Application::queryTimeInForce()
{
  char value;
  std::cout << std::endl
  << "1) Day" << std::endl
  << "2) IOC" << std::endl
  << "3) OPG" << std::endl
  << "4) GTC" << std::endl
  << "5) GTX" << std::endl
  << "TimeInForce: ";

  std::cin >> value;
  switch ( value )
  {
    case '1': return FIX::TimeInForce( FIX::TimeInForce_DAY );
    case '2': return FIX::TimeInForce( FIX::TimeInForce_IMMEDIATE_OR_CANCEL );
    case '3': return FIX::TimeInForce( FIX::TimeInForce_AT_THE_OPENING );
    case '4': return FIX::TimeInForce( FIX::TimeInForce_GOOD_TILL_CANCEL );
    case '5': return FIX::TimeInForce( FIX::TimeInForce_GOOD_TILL_CROSSING );
    default: throw std::exception();
  }
}
