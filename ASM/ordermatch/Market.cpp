#ifdef _MSC_VER
#pragma warning( disable : 4786 )
#endif

#include "Market.h"
#include <iostream>

bool Market::insert( const Order& order )
{
  if ( order.getSide() == Order::buy )
    m_bidOrders.insert( BidOrders::value_type( order.getPrice(), order ) );
  else
    m_askOrders.insert( AskOrders::value_type( order.getPrice(), order ) );
  return true;
}

void Market::erase( const Order& order )
{
  std::string id = order.getClientID();
  if ( order.getSide() == Order::buy )
  {
    BidOrders::iterator i;
    for ( i = m_bidOrders.begin(); i != m_bidOrders.end(); ++i )
      if ( i->second.getClientID() == id )
      {
        m_bidOrders.erase( i );
        return ;
      }
  }
  else if ( order.getSide() == Order::sell )
  {
    AskOrders::iterator i;
    for ( i = m_askOrders.begin(); i != m_askOrders.end(); ++i )
      if ( i->second.getClientID() == id )
      {
        m_askOrders.erase( i );
        return ;
      }
  }
}

bool Market::match( std::queue < Order > & orders )
{
  while ( true )
  {
    if ( !m_bidOrders.size() || !m_askOrders.size() )
      return orders.size() != 0;

    BidOrders::iterator iBid = m_bidOrders.begin();
    AskOrders::iterator iAsk = m_askOrders.begin();

    if ( iBid->second.getPrice() >= iAsk->second.getPrice() )
    {
      Order & bid = iBid->second;
      Order& ask = iAsk->second;

      match( bid, ask );
      orders.push( bid );
      orders.push( ask );

      if ( bid.isClosed() ) m_bidOrders.erase( iBid );
      if ( ask.isClosed() ) m_askOrders.erase( iAsk );
    }
    else
      return orders.size() != 0;
  }
}

Order& Market::find( Order::Side side, std::string id )
{
  if ( side == Order::buy )
  {
    BidOrders::iterator i;
    for ( i = m_bidOrders.begin(); i != m_bidOrders.end(); ++i )
      if ( i->second.getClientID() == id ) return i->second;
  }
  else if ( side == Order::sell )
  {
    AskOrders::iterator i;
    for ( i = m_askOrders.begin(); i != m_askOrders.end(); ++i )
      if ( i->second.getClientID() == id ) return i->second;
  }
  throw std::exception();
}


Order& Market::getLastBidOrder()
{
	BidOrders::iterator i;
	if ( i == m_bidOrders.end() ){
		throw std::exception();
	}
	else
		return m_bidOrders.begin()->second;
}

Order& Market::getLastAskOrder()
{
	AskOrders::iterator i;
	if ( i == m_askOrders.end() ){
		 throw std::exception();
	}

	else
		return m_askOrders.begin()->second;
}


std::vector<Order> Market::getBidOrders()
{
	  std::vector<Order> resp;
	  BidOrders::const_iterator iBid;

	  for ( iBid = m_bidOrders.begin(); iBid != m_bidOrders.end(); ++iBid )
		  resp.push_back(iBid->second);

	return resp;
}

std::vector<Order> Market::getAskOrders()
{
	  std::vector<Order> resp;
	  AskOrders::const_iterator iAsk;

	  for ( iAsk = m_askOrders.begin(); iAsk != m_askOrders.end(); ++iAsk )
		  resp.push_back(iAsk->second);
	return resp;
}

void Market::match( Order& bid, Order& ask )
{
  double price = ask.getPrice();
  int quantity = 0;

  if ( bid.getOpenQuantity() > ask.getOpenQuantity() )
    quantity = ask.getOpenQuantity();
  else
    quantity = bid.getOpenQuantity();

  bid.execute( price, quantity );
  ask.execute( price, quantity );
}

void Market::display() const
{
  BidOrders::const_iterator iBid;
  AskOrders::const_iterator iAsk;

  std::cout << "BIDS:" << std::endl;
  std::cout << "-----" << std::endl << std::endl;
  for ( iBid = m_bidOrders.begin(); iBid != m_bidOrders.end(); ++iBid )
    std::cout << iBid->second << std::endl;

  std::cout << std::endl << std::endl;

  std::cout << "ASKS:" << std::endl;
  std::cout << "-----" << std::endl << std::endl;
  for ( iAsk = m_askOrders.begin(); iAsk != m_askOrders.end(); ++iAsk )
    std::cout << iAsk->second << std::endl;
}
