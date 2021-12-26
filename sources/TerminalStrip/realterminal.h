/*
	Copyright 2006-2021 The QElectroTech Team
	This file is part of QElectroTech.

	QElectroTech is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 2 of the License, or
	(at your option) any later version.

	QElectroTech is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with QElectroTech.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef REALTERMINAL_H
#define REALTERMINAL_H

#include <QSharedPointer>
#include <QDomElement>
#include "../properties/elementdata.h"

class TerminalStrip;
class Element;
class TerminalElement;
class PhysicalTerminal;
struct TerminalStripBridge;

/**
 * @brief The RealTerminal class
 * Represent a real terminal.
 * A real terminal can be a drawed terminal in a folio
 * or a terminal set by user but not present
 * on any folio (for example a reserved terminal).
 *
 * When create a new instance of RealTerminal you must
 * call sharedRef() and only use the returned QSharedPointer
 * instead of the raw pointer
 */
class RealTerminal
{
		friend class TerminalStrip;
		friend class PhysicalTerminal;

	private:
		RealTerminal(TerminalStrip *strip, Element *element = nullptr);
		QSharedPointer<RealTerminal> sharedRef();
		QWeakPointer<RealTerminal> weakRef();

		bool fromXml(QDomElement xml_element, const QVector<TerminalElement *> &terminal_vector);
		QDomElement toXml(QDomDocument &parent_document) const;

	public:
		TerminalStrip *parentStrip() const;
		int level() const;
		QString label() const;
		QString Xref() const;
		QString cable() const;
		QString cableWire() const;
		QString conductor() const;

		ElementData::TerminalType type() const;
		ElementData::TerminalFunction function() const;

		bool isLed() const;
		bool isElement() const;
		bool isBridged() const;

		QSharedPointer<TerminalStripBridge> bridge() const;

		Element* element() const;
		QUuid elementUuid() const;
		QUuid uuid() const;

		static QString xmlTagName();

	private :
		QPointer<Element> m_element;
		QPointer<TerminalStrip> m_parent_terminal_strip;
		QUuid m_uuid = QUuid::createUuid();
		QWeakPointer<RealTerminal> m_this_weak;
};

#endif // REALTERMINAL_H
