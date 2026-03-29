import React, { useState } from 'react';
import { Link } from 'react-router-dom';
import './Header.css';
import glassIcon from './glass.png';

const Header = () => {
  const [isSearchOpen, setIsSearchOpen] = useState(false);
  const [searchQuery, setSearchQuery] = useState('');

  return (
    <header className="header">
      <div className="header-content">
        <div className="search-container">
          <button 
            className="search-btn" 
            onClick={() => setIsSearchOpen(!isSearchOpen)}
          >
            <span>search</span>
            <img src={glassIcon} alt="search" className="search-icon" />
          </button>
          {isSearchOpen && (
            <div className="search-popup">
              <input
                type="text"
                placeholder="Find a book..."
                value={searchQuery}
                onChange={(e) => setSearchQuery(e.target.value)}
                className="search-input"
                autoFocus
              />
            </div>
          )}
        </div>

        <Link to="/my-library" className="nav-link">my library</Link>

        <Link to="/" className="logo" data-full="bookhub">
          <span className="logo-short">bh</span>
          <span className="logo-full">bookhub</span>
        </Link>

        <Link to="/about" className="nav-link">about</Link>

        <div className="auth-links">
          <Link to="/sign-in" className="nav-link">sign in</Link>
          <span className="divider">/</span>
          <Link to="/sign-up" className="nav-link">sign up</Link>
        </div>
      </div>
    </header>
  );
};

export default Header;