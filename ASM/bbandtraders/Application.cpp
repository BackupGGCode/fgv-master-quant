#include "config.h"
#include "Application.h"
#include "quickfix/Session.h"

void Application::onLogon( const FIX::SessionID& sessionID )
{
  //std::cout << std::endl << "Logon - " << sessionID << std::endl;
  this->senderCompID = sessionID.getSenderCompID();
  this->targetCompID = sessionID.getTargetCompID();
  this->resetFlags();
}

void Application::resetFlags(){
	  getConfirmationTrade =false;
	  getConfirmationPartialExecutionTrade = false;
	  getConfirmationExecutionTrade = false;
	  getConfirmationCanceledTrade = false;
}

void Application::onLogout( const FIX::SessionID& sessionID )
{
  //std::cout << std::endl << "Logout - " << sessionID << std::endl;
}

void Application::fromApp( const FIX::Message& message, const FIX::SessionID& sessionID )
throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType )
{
  crack( message, sessionID );
  //std::cout << std::endl << "IN: " << message.toXML() << std::endl;

}


void Application::setStrategy(Strategy& strategy)
{
	this->strategy = strategy;
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

  //std::cout << std::endl << "OUT: " << message.toXML()  << std::endl;
}

void Application::onMessage
( const FIX42::ExecutionReport& message, const FIX::SessionID& ) {

    FIX::OrdStatus status;
    message.get(status);

    switch(status){
    case (FIX::OrdStatus_NEW):
		getConfirmationTrade=true;
    	break;
    case (FIX::OrdStatus_PARTIALLY_FILLED):
		getConfirmationPartialExecutionTrade =true;
		this->strategy.postTrade(message);
    	break;
    case (FIX::OrdStatus_FILLED):
		getConfirmationExecutionTrade =true;
		this->strategy.postTrade(message);
    	break;
    case (FIX::OrdStatus_CANCELED):
		getConfirmationCanceledTrade=true;
    	break;
    default:
    	break;

    }
}
void Application::onMessage
( const FIX42::OrderCancelReject&, const FIX::SessionID& ) {

}

void Application::onMessage
( const FIX42::MarketDataSnapshotFullRefresh&, const FIX::SessionID& ) {}

void Application::onMessage( const FIX42::Quote& message, const FIX::SessionID& ) {

}

void Application::waitGetCancelConfirmationResponse() {
	 while ( !getConfirmationCanceledTrade){
		 sleep(0.05); //ASAP
	}
}

void printState(StateBB state){

	switch(state){
		case NONE:
			std::cout << std::endl << " >[NONE]<";
			break;
		case OVERSOLD_IN:
			std::cout << std::endl << " >[OVERSOLD_IN]<";
			break;
		case OVERSOLD:
			std::cout << std::endl << " >[OVERSOLD]<";
			break;
		case OVERBOUGHT_IN:
			std::cout << std::endl << " >[OVERBOUGHT_IN]<";
			break;
		case OVERBOUGHT:
			std::cout << std::endl << " >[OVERBOUGHT]<";
			break;
		case OVERSOLD_OUT:
			std::cout << std::endl << " >[OVERSOLD_OUT]<";
			break;
		case OVERBOUGHT_OUT:
			std::cout << std::endl << " >[OVERBOUGHT_OUT]<";
			break;
		default:
			std::cout << std::endl ;
			break;
	}
}


void Application::run(){
	sleep(2);
  while (true){

    try{

    	sleep(strategy.initialTime);
    	this->strategy.preTrade();
    	printState(this->strategy.state);

    	if(this->strategy.state != NONE){
			if(	this->strategy.state == OVERSOLD_IN
				|| this->strategy.state== OVERBOUGHT_IN
				|| this->strategy.state== OVERSOLD_OUT
				|| this->strategy.state== OVERBOUGHT_OUT){

				SimpleOrder order = this->strategy.trade();
				this->sendOrder(order);

				sleep(strategy.cycleTime);

				if( getConfirmationPartialExecutionTrade == false
				    || getConfirmationExecutionTrade == false){

					this->cancelOrder(order);


				}
			}
    	}
    	this->resetFlags();



    }
    catch ( std::exception & e )
    {
      std::cout << "Problem! " << e.what() <<std::endl;
    }
  }
}


void Application::sendOrder(SimpleOrder order){


  if(order.orderQty >  0.0 && order.price >  0.0){
	  FIX42::NewOrderSingle newOrderSingle;
	  newOrderSingle.set( order.clOrdID );
	  newOrderSingle.set(FIX::HandlInst( '1' ));
	  newOrderSingle.set( order.symbol );
	  newOrderSingle.set( order.side );
	  newOrderSingle.set(FIX::TransactTime());
	  newOrderSingle.set( FIX::OrdType( FIX::OrdType_LIMIT ) );
	  newOrderSingle.set( order.orderQty );
	  newOrderSingle.set( FIX::TimeInForce( FIX::TimeInForce_DAY ) );
	  newOrderSingle.set( order.price );
	  setHeader( newOrderSingle.getHeader() );
	  FIX::Session::sendToTarget( newOrderSingle );
  }else{
	std::cout << "[Application::sendOrder] NOT SENT!!!"<<std::endl;
  	 }


}

void Application::cancelOrder(SimpleOrder order){

	if( order.orderQty >  0.0
	 && order.price >  0.0
	 && getConfirmationTrade == true){

	  FIX42::OrderCancelRequest orderCancelRequest;
	  FIX::ClOrdID clOrdID;
	  clOrdID = m_generator.genOrderID();
	  orderCancelRequest.set(FIX::ClOrdID( clOrdID ));
	  orderCancelRequest.set(FIX::OrigClOrdID (order.clOrdID));
	  orderCancelRequest.set( order.symbol );
	  orderCancelRequest.set( order.side );
	  orderCancelRequest.set(FIX::TransactTime());
	  orderCancelRequest.set( order.orderQty );

	  setHeader( orderCancelRequest.getHeader() );

	  FIX::Session::sendToTarget( orderCancelRequest );
	  //sleep(strategy.initialTime);
	  this->waitGetCancelConfirmationResponse();
	  std::cout << "[Application::cancelOrder] CANCELED!!!"<<std::endl;
	  this->strategy.state = NONE;

	}else{
		std::cout << "[Application::cancelOrder] *NOT* CANCELED!!!"<<std::endl;
	}
}

void Application::queryMarketDataRequest()
{

  FIX::MDReqID genMDReqID;
  genMDReqID = m_generator.genOrderID();
  FIX::MDReqID mdReqID( genMDReqID );
  FIX::SubscriptionRequestType subType( '1' );
  FIX::MarketDepth marketDepth( 2 );
  FIX::MDUpdateType mDUpdateType(1);
  FIX::AggregatedBook aggregatedBook(true);

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
  FIX::Session::sendToTarget( message );
}


void Application::setHeader( FIX::Header& header ){
  header.setField(this->senderCompID);
  header.setField( this->targetCompID );
}

